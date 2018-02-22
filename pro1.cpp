#include<bits/stdc++.h>
using namespace std;
struct  mycommand
{
    string action;
    long long orderid;
    long long timestamp;
    string symbol;
    string ordertype;
    string status;
    double price;
    int quantity;
};
struct  mycommand1
{
    string action;
    long long orderid;
    long long timestamp;
    string symbol;
    string ordertype;
    string status;
    double price;
    int quantity;
    string IOC;
};
long long previoustimestamp=0;
map<long long,long long> mapquantity;
map<long long,float> mapprice;
map<int,int> orderid_map;
string commandss;
bool cmpbuy(mycommand a,mycommand b)
{
    if(a.price!=b.price)
        return a.price>b.price;
    if(a.timestamp!=b.timestamp)
        return a.timestamp<b.timestamp;
    else
        return a.orderid<=b.orderid;
}
bool cmpsell(mycommand a,mycommand b)
{
    if(a.price!=b.price)
        return a.price<b.price;
    if(a.timestamp!=b.timestamp)
        return a.timestamp<b.timestamp;
    else
        return a.orderid<=b.orderid;
}
bool buysell1(mycommand1 a,mycommand1 b)
{
    if(a.IOC!=b.IOC)
        return a.IOC<b.IOC;
    if(a.price!=b.price)
        return a.price<b.price;
    if(a.timestamp!=b.timestamp)
        return a.timestamp<b.timestamp;
    else
        return a.orderid<=b.orderid;
}
long long convertstringtoint(string s)
{
    int flag=1;
    int l=s.length();
    long long val=0;
    for(int i=0;i<l;i++)
    {
        val=(val*10)+(s[i]-48);
    }
    return val;
}
double convertstringtofloat(string s)
{

    int l=s.length();
    int point=l;
    for(int i=0;i<l;i++)
    {
        if(s[i]=='.')
            point=i;
    }
    long long val=0;
    for(int i=0;i<point;i++)
    {
        val=(val*10)+(s[i]-48);
    }
    double multiplier=1.0;
    double decimal=0.0;
    for(int i=point+1;i<l;i++)
    {
        multiplier*=0.1;
        decimal=decimal+((s[i]-48)*multiplier);
    }
    return (val+decimal);
}
map<long long,mycommand> allcommands_orderid;
map<long long,mycommand> allcommands_commandid;
map<string,vector<mycommand> >buyitem,sellitem;
map<string,vector<mycommand1> > buysell;

//NEW COMMAND
void newcommand(int querynumber)
{
        string actioncopy;
        long long orderidcopy;
        long long timestampcopy;
        string symbolcopy;
        string ordertypecopy;
        string statuscopy;
        double pricecopy;
        int quantitycopy;
        int l=commandss.length();
        int i=0;
        int count1=0;
        int flag=0;
        while(1)
        {

            string s1="";
            for(int j=i;j<l;j++)
            {
                if(commandss[j]==',')
                {
                    i=j+1;
                    break;
                }
                s1+=commandss[j];
            }
            if(count1==0)
            {
                actioncopy=s1;

            }
            if(count1==1)
            {
                orderidcopy=convertstringtoint(s1);
                if(orderid_map[convertstringtoint(s1)]==1)
                {
                    flag=1;
                   // cout<<"count1 "<<count1;
                }
            }
            if(count1==2)
            {
                 timestampcopy=convertstringtoint(s1);
                 if(convertstringtoint(s1)<previoustimestamp)
                    {
                    flag=1;
                    //cout<<"count1 "<<count1;
                    }
            }
            if(count1==3)
            {
                symbolcopy=s1;
            }
            if(count1==4)
            {
                ordertypecopy=s1;
                if(s1!="M" && s1!="L" && s1!="I")
                    {
                    flag=1;
                    //cout<<"count1 "<<count1;
                    }
            }
            if(count1==5)
            {
                statuscopy=s1;
                if(s1!="B" && s1!="S")
                    {
                    flag=1;
                  //  cout<<"count1 "<<count1;
                    }
            }
            if(count1==6)
            {
                pricecopy=convertstringtofloat(s1);
                if(convertstringtofloat(s1)<0)
                    {
                    flag=1;
                   // cout<<"count1 "<<count1;
                    }
            }
            if(count1==7)
            {
                quantitycopy=convertstringtoint(s1);
                if(convertstringtoint(s1)<0 || convertstringtoint(s1)!=convertstringtofloat(s1))
                    {
                    flag=1;
                    //cout<<"count1 "<<count1;
                    }
            }
            count1++;
            if(count1==8)
                break;
        }
        if(flag==1)
       {

           cout<<(orderidcopy)<<" - "<<"Reject - 303 - Invalid order details\n";
       }
       else
       {
             cout<<(orderidcopy)<<" - "<<"Accept\n";
             orderid_map[orderidcopy]=1;
             previoustimestamp=timestampcopy;
             mycommand1 keepcopy;

             keepcopy.action=actioncopy;
             keepcopy.orderid=orderidcopy;
             keepcopy.timestamp=timestampcopy;
             keepcopy.symbol=symbolcopy;
             if(ordertypecopy=="M")
             keepcopy.IOC="0";
             else
             keepcopy.IOC="1";
             keepcopy.ordertype=ordertypecopy;
             keepcopy.status=statuscopy;
             keepcopy.price=pricecopy;
             keepcopy.quantity=quantitycopy;

             allcommands_commandid[querynumber].action=actioncopy;
             allcommands_commandid[querynumber].orderid=orderidcopy;
             allcommands_commandid[querynumber].timestamp=timestampcopy;
             allcommands_commandid[querynumber].symbol=symbolcopy;
             allcommands_commandid[querynumber].ordertype=ordertypecopy;
             allcommands_commandid[querynumber].status=statuscopy;
             allcommands_commandid[querynumber].price=pricecopy;
             allcommands_commandid[querynumber].quantity=quantitycopy;
             mapquantity[orderidcopy]=quantitycopy;
             mapprice[orderidcopy]=pricecopy;
             //Order_ID
             allcommands_orderid[orderidcopy].action=actioncopy;
             allcommands_orderid[orderidcopy].orderid=orderidcopy;
             allcommands_orderid[orderidcopy].timestamp=timestampcopy;
             allcommands_orderid[orderidcopy].symbol=symbolcopy;
             allcommands_orderid[orderidcopy].ordertype=ordertypecopy;
             allcommands_orderid[orderidcopy].status=statuscopy;
             allcommands_orderid[orderidcopy].price=pricecopy;
             allcommands_orderid[orderidcopy].quantity=quantitycopy;
             buysell[symbolcopy].push_back(keepcopy);
              if(statuscopy=="B")
                buyitem[symbolcopy].push_back(allcommands_orderid[orderidcopy]);
              else
                sellitem[symbolcopy].push_back(allcommands_orderid[orderidcopy]);
       }
}
void amendcommand()
{
        string actionamend,actionnew;
        long long orderidamend,orderidnew;
        long long timestampamend,timestampnew;
        string symbolamend,symbolnew;
        string ordertypeamend,ordertypenew;
        string statusamend,statusnew;
        double priceamend,pricenew;
        int quantityamend,quantitynew;
        int l=commandss.length();
        int i=0;
        int count1=0;
        int flag=0;
        while(1)
        {

            string s1="";
            for(int j=i;j<l;j++)
            {
                if(commandss[j]==',')
                {
                    i=j+1;
                    break;
                }
                s1+=commandss[j];
            }
            if(count1==0)
            {
                actionamend=s1;

            }
            if(count1==1)
            {
                orderidamend=convertstringtoint(s1);
                if(allcommands_orderid.find(orderidamend)==allcommands_orderid.end())
                    flag=2;
                else
                {
                    symbolnew=allcommands_orderid[orderidamend].symbol;
                    ordertypenew=allcommands_orderid[orderidamend].ordertype;
                    statusnew=allcommands_orderid[orderidamend].status;
                    pricenew=allcommands_orderid[orderidamend].price;
                    quantitynew=allcommands_orderid[orderidamend].quantity;
                }
            }
            if(count1==2)
            {
                 timestampamend=convertstringtoint(s1);
                 if(flag==2)
                    continue;
                 if(convertstringtoint(s1)<previoustimestamp)
                    {
                    flag=1;
                    //cout<<"count1 "<<count1;
                    }
            }
            if(count1==3)
            {
                symbolamend=s1;
                 if(flag==2)
                    continue;
                if(symbolnew!=symbolamend)
                    flag=1;
            }
            if(count1==4)
            {
                ordertypeamend=s1;
                 if(flag==2)
                    continue;
                if(ordertypenew!=ordertypeamend )
                    {
                    flag=1;
                    //cout<<"count1 "<<count1;
                    }
            }
            if(count1==5)
            {
                statusamend=s1;
                 if(flag==2)
                    continue;
                if(statusamend!=statusnew)
                    {
                    flag=1;
                  //  cout<<"count1 "<<count1;
                    }
            }
            if(count1==6)
            {
                priceamend=convertstringtofloat(s1);
                 if(flag==2)
                    continue;
                if(convertstringtofloat(s1)<0)
                    {
                    flag=1;
                   // cout<<"count1 "<<count1;
                    }
            }
            if(count1==7)
            {
                quantityamend=convertstringtoint(s1);
                 if(flag==2)
                    continue;
                if(convertstringtoint(s1)<0 || convertstringtoint(s1)!=convertstringtofloat(s1))
                    {
                    flag=1;
                    //cout<<"count1 "<<count1;
                    }
            }
            count1++;
            if(count1==8)
                break;
        }
        if(flag==1)
       {

           cout<<(orderidamend)<<" - "<<"AmendReject - 101 - Invalid amendment details\n";
       }
       else if(flag==2)
       {
            cout<<(orderidamend)<<" - "<<"AmendReject - 404 - Order does not exist\n";
       }
       else
       {
             cout<<(orderidamend)<<" - "<<"AmendAccept\n";
              allcommands_orderid[orderidamend].quantity=quantityamend;
              allcommands_orderid[orderidamend].price=priceamend;
             /* if(mapquantity[orderidamend]<quantityamend)
              {
                  auto it=(buysell[orderidamend]->second).find()
              }*/
              mapquantity[orderidamend]=quantityamend;
              mapprice[orderidamend]=priceamend;
       }
}
void matchcommand()
{
        long long timestampmatch;
        string symbolmatch="";
        int flag=0;
        int i=0;
        int count1=0;
        int l=commandss.length();
        while(1)
        {

            string s1="";
            for(int j=i;j<l;j++)
            {
                if(commandss[j]==',')
                {
                    i=j+1;
                    break;
                }
                s1+=commandss[j];
                if(j==(l-2))
                    i=(l-1);
            }
            if(count1==0)
            {

            }
            if(count1==1)
            {
                 timestampmatch=convertstringtoint(s1);
                 if(convertstringtoint(s1)<previoustimestamp)
                    {
                    flag=1;
                    //cout<<"count1 "<<count1;
                    }
                    if(i==(l-1))
                        break;
            }
            if(count1==2)
            {
                symbolmatch=s1;
            }
            count1++;
            if(count1==3)
                break;
        }
        //cout<<symbolmatch<<endl;
        if(symbolmatch=="")
        {
            for (map<string,vector<mycommand> >::iterator it=buyitem.begin();it!=buyitem.end();++it)
            {
                sort(((it->second).begin()),((it->second).end()),cmpbuy);
            }
            for (map<string,vector<mycommand> >::iterator it=sellitem.begin();it!=sellitem.end();++it)
            {
                sort(((it->second).begin()),((it->second).end()),cmpsell);
            }
            for (map<string,vector<mycommand1> >::iterator it=buysell.begin();it!=buysell.end();++it)
            {
                sort(((it->second).begin()),((it->second).end()),buysell1);
            }
             for (map<string,vector<mycommand1> >::iterator it=buysell.begin();it!=buysell.end();++it)
             {
                string mysymbol=(it->first);
                for(int i=0;i<(it->second).size();i++)
                {
                    string myordertype=((it->second)[i]).IOC;
                    string mystatus=((it->second))[i].status;
                    long long orderid1=((it->second))[i].orderid;
                    long long quantity=mapquantity[orderid1];
                    if(quantity==0LL)
                        continue;
                    if(mystatus=="B")
                    {
                         map<string,vector<mycommand> >::iterator it1=sellitem.find(mysymbol);

                        if(it1==sellitem.end())
                        continue;
                        if(myordertype=="0")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                                 long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0)
                                    continue;
                             if(mapquantity[orderid1]>mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid2]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    mapquantity[orderid1]-=mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if(mapquantity[orderid1]<mapquantity[orderid2])
                            {
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid1]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    mapquantity[orderid2]-=mapquantity[orderid1];
                                    mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid1]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    mapquantity[orderid2]=0;
                                    mapquantity[orderid1]=0;

                                   break;
                            }

                        }

                    }
                    if(myordertype=="1")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                               long long orderid2=((it1->second))[j].orderid;

                                if(mapquantity[orderid2]==0)
                                    continue;
                                   // cout<<orderid1<<" "<<orderid2<<endl;
                                if(mapprice[orderid1]<mapprice[orderid2])
                                    break;
                             if( mapquantity[orderid1]> mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<< mapquantity[orderid2]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid2]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    mapquantity[orderid1]-= mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if( mapquantity[orderid1]< mapquantity[orderid2])
                            {
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<< mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<< mapquantity[orderid1]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                     mapquantity[orderid2]-= mapquantity[orderid1];
                                     mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<< mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<< mapquantity[orderid1]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                     mapquantity[orderid1]=0;
                                     mapquantity[orderid2]=0;

                                   break;
                            }

                        }

                    }
                }


                if(mystatus=="S")
                    {
                         map<string,vector<mycommand> >::iterator it1=buyitem.find(mysymbol);
                        if(it1==buyitem.end())
                        continue;

                        if(myordertype=="0")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                                long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0)
                                    continue;
                             if(mapquantity[orderid1]>mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid1]-=mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if(mapquantity[orderid1]<mapquantity[orderid2])
                            {
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid1]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]-=mapquantity[orderid1];
                                    mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]=0;
                                    mapquantity[orderid1]=0;

                                   break;
                            }

                        }

                    }
                    if(myordertype=="1")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                                 long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0)
                                    continue;
                               if(mapprice[orderid1]>mapprice[orderid2])
                                    break;
                             if(mapquantity[orderid1]>mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid1]-=mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if(mapquantity[orderid1]<mapquantity[orderid2])
                            {
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid1]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]-=mapquantity[orderid1];
                                    mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]=0;
                                    mapquantity[orderid1]=0;

                                   break;
                            }
                            }
                    }

                }
                    }
                }
            for (map<string,vector<mycommand1> >::iterator it=buysell.begin();it!=buysell.end();++it)
             {
                for(int i=0;i<(it->second).size();i++)
                {
                    if(((it->second)[i]).ordertype=="I")
                        mapquantity[(it->second)[i].orderid]=0;
                }
            }
        }
        else
        {
            if(buyitem.find(symbolmatch)!=buyitem.end() && sellitem.find(symbolmatch)!=sellitem.end() )
            {
                sort(buyitem[symbolmatch].begin(),buyitem[symbolmatch].end(),cmpbuy);
                sort(sellitem[symbolmatch].begin(),sellitem[symbolmatch].end(),cmpsell);
                  sort(buysell[symbolmatch].begin(),buysell[symbolmatch].end(),buysell1);
                int i=0;
                int j=0;
                map<string,vector<mycommand1> >::iterator it=buysell.find(symbolmatch);
                for(int i=0;i<(it->second).size();i++)
                {
                    string myordertype=((it->second)[i]).ordertype;
                    string mystatus=((it->second))[i].status;
                    long long orderid1=((it->second))[i].orderid;
                    long long quantity=((it->second))[i].quantity;
                    if(quantity==0LL)
                        continue;
                    if(mystatus=="B")
                    {
                         map<string,vector<mycommand> >::iterator it1=sellitem.find(symbolmatch);

                        if(it1==sellitem.end())
                        continue;

                        if(myordertype=="0")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                                 long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0)
                                    continue;
                             if(mapquantity[orderid1]>mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid2]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    mapquantity[orderid1]-=mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if(mapquantity[orderid1]<mapquantity[orderid2])
                            {
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid1]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    mapquantity[orderid2]-=mapquantity[orderid1];
                                    mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid1]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    mapquantity[orderid2]=0;
                                    mapquantity[orderid1]=0;

                                   break;
                            }

                        }

                    }
                    if(myordertype=="1")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                               long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0)
                                    continue;
                               if(mapprice[orderid1]<mapprice[orderid2])
                                    break;
                             if( mapquantity[orderid1]> mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<< mapquantity[orderid2]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid2]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    mapquantity[orderid1]-= mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if( mapquantity[orderid1]< mapquantity[orderid2])
                            {
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<< mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<< mapquantity[orderid1]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                     mapquantity[orderid2]-= mapquantity[orderid1];
                                     mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<< mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<< mapquantity[orderid1]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                     mapquantity[orderid1]=0;
                                     mapquantity[orderid2]=0;

                                   break;
                            }

                        }

                    }
                }


                if(mystatus=="S")
                    {
                         map<string,vector<mycommand> >::iterator it1=buyitem.find(symbolmatch);
                        if(it1==buyitem.end())
                        continue;

                        if(myordertype=="0")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                                long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0)
                                    continue;
                             if(mapquantity[orderid1]>mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid1]-=mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if(mapquantity[orderid1]<mapquantity[orderid2])
                            {
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid1]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]-=mapquantity[orderid1];
                                    mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]=0;
                                    mapquantity[orderid1]=0;

                                   break;
                            }

                        }

                    }
                    if(myordertype=="1")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                                 long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0)
                                    continue;
                               if(mapprice[orderid1]>mapprice[orderid2])
                                    break;
                             if(mapquantity[orderid1]>mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid1]-=mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if(mapquantity[orderid1]<mapquantity[orderid2])
                            {
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid1]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]-=mapquantity[orderid1];
                                    mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]=0;
                                    mapquantity[orderid1]=0;

                                   break;
                            }
                            }
                    }

                }
            }
                map<string,vector<mycommand1> >:: iterator it2=buysell.find(symbolmatch);

                    for(int i=0;i<(it2->second).size();i++)
                    {
                        if(((it2->second)[i]).ordertype=="IOC")
                             mapquantity[((it2->second)[i]).orderid]=0;
                    }


            }
            else
                return;
        }


}
void cancelcommand()
{
        long long timestampcancel,orderidcancel;
        string symbolcancel="";
        int flag=0;
        int i=0;
        int count1=0;
        int l=commandss.length();
        while(1)
        {

            string s1="";
            for(int j=i;j<l;j++)
            {
                if(commandss[j]==',')
                {
                    i=j+1;
                    break;
                }
                s1+=commandss[j];
            }
            if(count1==0)
            {

            }
            if(count1==1)
            {
                 orderidcancel=convertstringtoint(s1);
            }
            if(count1==2)
            {
                 timestampcancel=convertstringtoint(s1);
                 if(convertstringtoint(s1)<previoustimestamp)
                    {
                    flag=1;
                    //cout<<"count1 "<<count1;
                    }

            }

            count1++;
            if(count1==3)
                break;

        }
        if((mapquantity.find(orderidcancel)==mapquantity.end()) || (flag=1))
        {
            cout<<(orderidcancel)<<" - "<<"CancelReject - 404 - Order does not exist\n";
        }
        else if(mapquantity[orderidcancel]==0)
        {
            cout<<(orderidcancel)<<" - "<<"CancelReject - 404 - Order does not exist\n";
        }
        else
        {
             cout<<(orderidcancel)<<" - "<<"CancelAccept\n";
             mapquantity[orderidcancel]==0;
        }
}
void querycommand()
{
        long long timestampquery=LLONG_MAX;
        map<long long ,long long> visited;
        string symbolquery="";

        int flag=0;
        int i=0;
        int count1=0;
        int l=commandss.length();
        while(1)
        {

            string s1="";
            for(int j=i;j<l;j++)
            {
                if(commandss[j]==',')
                {
                    i=j+1;
                    break;
                }
                s1+=commandss[j];
                if(j==(l-2))
                    i=(l-1);
            }
            if(count1==0)
            {
                if(i==(l-1))
                        break;
            }
            if(count1==1)
            {
                if((s1[0]-48)>=0 && (s1[0]-48)<=9)
                {
                 timestampquery=convertstringtoint(s1);
                }
                else
                {

                 symbolquery=s1;   
                }
                if(i==(l-1))
                        break;
                
            }
            if(count1==2)
            {
                if((s1[0]-48)>=0 && (s1[0]-48)<=9)
                {
                 timestampquery=convertstringtoint(s1);
                }
                else
                {

                 symbolquery=s1;   
                }
            }
            count1++;
            if(count1==3)
                break;
        }
        //cout<<symbolmatch<<endl;
        if(symbolmatch=="")
        {
            for (map<string,vector<mycommand> >::iterator it=buyitem.begin();it!=buyitem.end();++it)
            {
                sort(((it->second).begin()),((it->second).end()),cmpbuy);
            }
            for (map<string,vector<mycommand> >::iterator it=sellitem.begin();it!=sellitem.end();++it)
            {
                sort(((it->second).begin()),((it->second).end()),cmpsell);
            }
            for (map<string,vector<mycommand1> >::iterator it=buysell.begin();it!=buysell.end();++it)
            {
                sort(((it->second).begin()),((it->second).end()),buysell1);
            }
             for (map<string,vector<mycommand1> >::iterator it=buysell.begin();it!=buysell.end();++it)
             {
                string mysymbol=(it->first);
               
                int count1=0;

                for(int i=0;i<(it->second).size();i++)
                {
                    if(count1==5)
                        break;
                    int flag=0;
                    string myordertype=((it->second)[i]).IOC;
                    string mystatus=((it->second))[i].status;
                    long long orderid1=((it->second))[i].orderid;
                    if(visited[orderid1]==100)
                        continue;
                    long long quantity=mapquantity[orderid1];
                    if(quantity==0LL)
                        continue;
                    if(mystatus=="B")
                    {
                         map<string,vector<mycommand> >::iterator it1=sellitem.find(mysymbol);

                        if(it1==sellitem.end())
                        {
                             cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"||"<<endl;
                                    visited[orderid1]=100;
                                    count1++;
                                   // mapquantity[orderid1]-=mapquantity[orderid2];
                                   // mapquantity[orderid2]=0;
                                    continue;
                        }
                        
                        if(myordertype=="0")
                        {
                            while(1)
                            {
                                if(j==(it1->second).size())
                                    break;
                                 long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0 || visited[orderid2]==100)
                                {
                                    j++;
                                    count1++;
                                    continue;
                                }
                            
                               cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid2]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                  j++;
                                  visited[orderid1]=100;
                                   visited[orderid2]=100;
                                   count1++;
                                  flag=1;
                                  break;

                            }
                            

                    }
                    if(myordertype=="1")
                        {
                           while(1)
                            {
                               long long orderid2=((it1->second))[j].orderid;
                               if(mapprice[orderid1]<mapprice[orderid2])
                                    break;
                                 if(j==(it1->second).size())
                                    break;
                                if(mapquantity[orderid2]==0 || visited[orderid2]==100)
                                {
                                    j++;
                                    continue;
                                }
                            
                               cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid2]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                  j++;
                                  visited[orderid1]=100;
                                   visited[orderid2]=100;
                                   count1++;
                                  flag=1;
                                  break;
                            }

                        }
                        if(visited[orderid1]!=100)
                            {
                                 cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"||"<<endl;
                                    visited[orderid1]=100;
                                    count1++;
                            }
                }


                if(mystatus=="S")
                    {
                         map<string,vector<mycommand> >::iterator it1=buyitem.find(mysymbol);
                        if(it1==buyitem.end())
                        continue;

                        if(myordertype=="0")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                                long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0)
                                    continue;
                             if(mapquantity[orderid1]>mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid1]-=mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if(mapquantity[orderid1]<mapquantity[orderid2])
                            {
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid1]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]-=mapquantity[orderid1];
                                    mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]=0;
                                    mapquantity[orderid1]=0;

                                   break;
                            }

                        }

                    }
                    if(myordertype=="1")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                                 long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0)
                                    continue;
                               if(mapprice[orderid1]>mapprice[orderid2])
                                    break;
                             if(mapquantity[orderid1]>mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid1]-=mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if(mapquantity[orderid1]<mapquantity[orderid2])
                            {
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid1]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]-=mapquantity[orderid1];
                                    mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]=0;
                                    mapquantity[orderid1]=0;

                                   break;
                            }
                            }
                    }

                }
                    }
                }
            for (map<string,vector<mycommand1> >::iterator it=buysell.begin();it!=buysell.end();++it)
             {
                for(int i=0;i<(it->second).size();i++)
                {
                    if(((it->second)[i]).ordertype=="I")
                        mapquantity[(it->second)[i].orderid]=0;
                }
            }
        }
        else
        {
            if(buyitem.find(symbolmatch)!=buyitem.end() && sellitem.find(symbolmatch)!=sellitem.end() )
            {
                sort(buyitem[symbolmatch].begin(),buyitem[symbolmatch].end(),cmpbuy);
                sort(sellitem[symbolmatch].begin(),sellitem[symbolmatch].end(),cmpsell);
                  sort(buysell[symbolmatch].begin(),buysell[symbolmatch].end(),buysell1);
                int i=0;
                int j=0;
                map<string,vector<mycommand1> >::iterator it=buysell.find(symbolmatch);
                for(int i=0;i<(it->second).size();i++)
                {
                    string myordertype=((it->second)[i]).ordertype;
                    string mystatus=((it->second))[i].status;
                    long long orderid1=((it->second))[i].orderid;
                    long long quantity=((it->second))[i].quantity;
                    if(quantity==0LL)
                        continue;
                    if(mystatus=="B")
                    {
                         map<string,vector<mycommand> >::iterator it1=sellitem.find(symbolmatch);

                        if(it1==sellitem.end())
                        continue;

                        if(myordertype=="0")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                                 long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0)
                                    continue;
                             if(mapquantity[orderid1]>mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid2]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    mapquantity[orderid1]-=mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if(mapquantity[orderid1]<mapquantity[orderid2])
                            {
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid1]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    mapquantity[orderid2]-=mapquantity[orderid1];
                                    mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid1]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    mapquantity[orderid2]=0;
                                    mapquantity[orderid1]=0;

                                   break;
                            }

                        }

                    }
                    if(myordertype=="1")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                               long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0)
                                    continue;
                               if(mapprice[orderid1]<mapprice[orderid2])
                                    break;
                             if( mapquantity[orderid1]> mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<< mapquantity[orderid2]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<<mapquantity[orderid2]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    mapquantity[orderid1]-= mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if( mapquantity[orderid1]< mapquantity[orderid2])
                            {
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<< mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<< mapquantity[orderid1]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                     mapquantity[orderid2]-= mapquantity[orderid1];
                                     mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<< mapquantity[orderid1]<<","
                                    <<mapprice[orderid1]<<"|"<<mapprice[orderid2]<<","<< mapquantity[orderid1]<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                     mapquantity[orderid1]=0;
                                     mapquantity[orderid2]=0;

                                   break;
                            }

                        }

                    }
                }


                if(mystatus=="S")
                    {
                         map<string,vector<mycommand> >::iterator it1=buyitem.find(symbolmatch);
                        if(it1==buyitem.end())
                        continue;

                        if(myordertype=="0")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                                long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0)
                                    continue;
                             if(mapquantity[orderid1]>mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid1]-=mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if(mapquantity[orderid1]<mapquantity[orderid2])
                            {
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid1]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]-=mapquantity[orderid1];
                                    mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]=0;
                                    mapquantity[orderid1]=0;

                                   break;
                            }

                        }

                    }
                    if(myordertype=="1")
                        {
                            for(int j=0;j<(it1->second).size();j++)
                            {
                                 long long orderid2=((it1->second))[j].orderid;
                                if(mapquantity[orderid2]==0)
                                    continue;
                               if(mapprice[orderid1]>mapprice[orderid2])
                                    break;
                             if(mapquantity[orderid1]>mapquantity[orderid2])
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid1]-=mapquantity[orderid2];
                                    mapquantity[orderid2]=0;
                                    i--;
                                    break;

                            }
                            else if(mapquantity[orderid1]<mapquantity[orderid2])
                            {
                                    cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid1]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid1]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]-=mapquantity[orderid1];
                                    mapquantity[orderid1]=0;
                                     break;
                            }
                            else
                            {
                               cout<<(it1->first)<<"|"<<(it1->second)[j].orderid<<","<<(it1->second)[j].ordertype<<","<<mapquantity[orderid2]<<","
                                    <<mapprice[orderid2]<<"|"<<mapprice[orderid1]<<","<<mapquantity[orderid2]<<","<<(it->second)[i].ordertype
                                    <<","<<(it->second)[i].orderid<<endl;
                                    mapquantity[orderid2]=0;
                                    mapquantity[orderid1]=0;

                                   break;
                            }
                            }
                    }

                }
            }
                map<string,vector<mycommand1> >:: iterator it2=buysell.find(symbolmatch);

                    for(int i=0;i<(it2->second).size();i++)
                    {
                        if(((it2->second)[i]).ordertype=="IOC")
                             mapquantity[((it2->second)[i]).orderid]=0;
                    }


            }
            else
                return;
        }


}  
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int queries;
    cin>>queries;
    int queriescopy=queries;
    int querynumber=0;
    int i;
    while(queries--)
    {
        cin>>commandss;
        if(commandss[0]=='N')
        {
            newcommand(querynumber);
            querynumber++;
        }
        if(commandss[0]=='A')
        {
            amendcommand();
        }
        if(commandss[0]=='M')
        {
            matchcommand();
        }
        if(commandss[0]=='X')
        {
            cancelcommand();
        }
         if(commandss[0]=='Q')
        {
            querycommand();
        }

    }
    /*for(int i=0;i<queriescopy;i++)
    {
        cout<<allcommands[i].action<<" "<<allcommands[i].orderid<<" "<<allcommands[i].timestamp<<" "<<allcommands[i].symbol<<" "<<allcommands[i].ordertype<<" "<<allcommands[i].status<<" "<<allcommands[i].price<<" "<<allcommands[i].quantity<<" "<<endl;
    }*/
}
/*
8
N,1,0000001,ALN,L,B,60.90,100
N,11,0000002,XYZ,L,B,60.90,200
N,110,0000003,XYZ,L,S,60.90,100
N,112,0000003,XYZ,L,S,60.90,120
N,10,0000006,ALN,L,S,60.90,100
M,00010


8
N,1,0000001,ALN,L,B,60.90,100
N,11,0000002,XYZ,L,B,60.90,200
N,110,0000003,XYZ,L,S,60.90,100
N,112,0000003,XYZ,L,S,60.90,120
N,10,0000006,ALN,L,S,60.90,100
M,00010,ALN
*/
