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
long long previoustimestamp=0;
map<long long,long long> mapquantity;
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
map<string,vector<mycommand> >buyitem;
map<string,vector<mycommand> >sellitem;
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
                if(s1!="M" && s1!="L" && s1!="IOC")
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
             allcommands_commandid[querynumber].action=actioncopy;
             allcommands_commandid[querynumber].orderid=orderidcopy;
             allcommands_commandid[querynumber].timestamp=timestampcopy;
             allcommands_commandid[querynumber].symbol=symbolcopy;
             allcommands_commandid[querynumber].ordertype=ordertypecopy;
             allcommands_commandid[querynumber].status=statuscopy;
             allcommands_commandid[querynumber].price=pricecopy;
             allcommands_commandid[querynumber].quantity=quantitycopy;
             mapquantity[orderidcopy]=quantitycopy;
             //Order_ID
             allcommands_orderid[orderidcopy].action=actioncopy;
             allcommands_orderid[orderidcopy].orderid=orderidcopy;
             allcommands_orderid[orderidcopy].timestamp=timestampcopy;
             allcommands_orderid[orderidcopy].symbol=symbolcopy;
             allcommands_orderid[orderidcopy].ordertype=ordertypecopy;
             allcommands_orderid[orderidcopy].status=statuscopy;
             allcommands_orderid[orderidcopy].price=pricecopy;
             allcommands_orderid[orderidcopy].quantity=quantitycopy;
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
             for (map<string,vector<mycommand> >::iterator it=buyitem.begin();it!=buyitem.end();++it)
             {
                 //cout<<(it->first)<<endl;
                map<string,vector<mycommand> >::iterator it1=sellitem.find((it->first));
                if(it1==sellitem.end())
                    continue;
                else
                {
                   // cout<<(it1->first)<<endl;
                    int i=0;
                    int j=0;
                    /*for(int a=0;a<(it->second).size();a++)
                    {
                        cout<<(it->second)[a].price<<" "<<(it->second)[a].quantity<<"\n";
                    }
                    for(int b=0;b<(it1->second).size();b++)
                    {
                        cout<<(it1->second)[b].price<<" "<<(it1->second)[b].quantity<<"\n";
                    }*/
                    while(1)
                    {
                        if(i==(it->second).size() || j==(it1->second).size())
                            break;
                        if((it->second)[i].quantity==0)
                        {
                            i++;
                            continue;
                        }
                        if((it1->second)[j].quantity==0)
                        {
                            j++;
                            continue;
                        }
                        if((it->second)[i].price >= (it1->second)[j].price)
                        {
                            if((it->second)[i].quantity>(it1->second)[j].quantity)
                            {
                                //cout<<(it->second)[i].quantity<<" "<<(it1->second)[j].quantity<<endl;
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<(it1->second)[j].quantity<<","
                                    <<(it->second)[i].price<<"|"<<(it1->second)[j].price<<","<<(it1->second)[j].quantity<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    (it->second)[i].quantity-=((it1->second)[j].quantity);
                                    (it1->second)[j].quantity=0;
                                    mapquantity[(it1->second)[j].orderid]=0;
                                    mapquantity[(it->second)[i].orderid]=(it->second)[i].quantity;
                                    j++;
                            }
                            else if((it->second)[i].quantity<(it1->second)[j].quantity)
                            {
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<(it->second)[i].quantity<<","
                                    <<(it->second)[i].price<<"|"<<(it1->second)[j].price<<","<<(it->second)[i].quantity<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    (it1->second)[j].quantity-=((it->second)[i].quantity);
                                    (it->second)[i].quantity=0;
                                    mapquantity[(it1->second)[j].orderid]=(it1->second)[j].quantity;
                                    mapquantity[(it->second)[i].orderid]=0;
                                    i++;
                            }
                            else
                            {
                               cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<(it->second)[i].quantity<<","
                                    <<(it->second)[i].price<<"|"<<(it1->second)[j].price<<","<<(it->second)[i].quantity<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    (it1->second)[j].quantity=0;
                                    (it->second)[i].quantity=0;
                                     mapquantity[(it->second)[i].orderid]=0;
                                      mapquantity[(it1->second)[j].orderid]=0;

                                    i++;
                                    j++;
                            }
                        }
                        else
                            break;
                    }
                }
             }
        for (map<string,vector<mycommand> >::iterator it=buyitem.begin();it!=buyitem.end();++it)
             {
                for(int i=0;i<((it->second).size());i++)
                {
                    if((((it->second)[i]).ordertype)=="IOC")
                    {
                        ((it->second)[i]).quantity=0;
                         mapquantity[(it->second)[i].orderid]=0;
                       
                    }
                }
            }
            for (map<string,vector<mycommand> >::iterator it=sellitem.begin();it!=sellitem.end();++it)
             {
                for(int i=0;i<((it->second).size());i++)
                {
                    if((((it->second)[i]).ordertype)=="IOC")
                    {
                        ((it->second)[i]).quantity=0;
                        mapquantity[(it->second)[i].orderid]=0;
                    }
                }
            }
        }
        else
        {
            if(buyitem.find(symbolmatch)!=buyitem.end() && sellitem.find(symbolmatch)!=sellitem.end() )
            {
                sort(buyitem[symbolmatch].begin(),buyitem[symbolmatch].end(),cmpbuy);
                sort(sellitem[symbolmatch].begin(),sellitem[symbolmatch].end(),cmpsell);
                int i=0;
                int j=0;
                map<string,vector<mycommand> >::iterator it=buyitem.find(symbolmatch);
                map<string,vector<mycommand> >::iterator it1=sellitem.find(symbolmatch);
                while(1)
                    {
                        if(i==(it->second).size() || j==(it1->second).size())
                            break;
                            if((it->second)[i].quantity==0)
                        {
                            i++;
                            continue;
                        }
                        if((it1->second)[j].quantity==0)
                        {
                            j++;
                            continue;
                        }
                        if((it->second)[i].price >= (it1->second)[j].price)
                        {
                            if((it->second)[i].quantity>(it1->second)[j].quantity)
                            {
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<(it1->second)[j].quantity<<","
                                    <<(it->second)[i].price<<"|"<<(it1->second)[j].price<<","<<(it1->second)[j].quantity<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    ((it->second)[i].quantity)-=(it1->second)[j].quantity;
                                    (it1->second)[j].quantity=0;
                                    mapquantity[(it->second)[i].orderid]=(it->second)[i].quantity;
                                    mapquantity[(it1->second)[j].orderid]=0;
                                    j++;
                            }
                            else if((it->second)[i].quantity<(it1->second)[j].quantity)
                            {
                                    cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<(it->second)[i].quantity<<","
                                    <<(it->second)[i].price<<"|"<<(it1->second)[j].price<<","<<(it->second)[i].quantity<<","<<(it1->second)[j].ordertype
                                    <<","<<(it1->second)[j].orderid<<endl;
                                    ((it1->second)[j].quantity)-=(it->second)[i].quantity;
                                    (it->second)[i].quantity=0;
                                    mapquantity[(it->second)[i].orderid]=0;
                                    mapquantity[(it1->second)[j].orderid]=(it1->second)[j].quantity;
                                    i++;
                            }
                            else
                            {
                               cout<<(it->first)<<"|"<<(it->second)[i].orderid<<","<<(it->second)[i].ordertype<<","<<(it->second)[i].quantity<<","
                                    <<(it->second)[i].price<<"|"<<(it1->second)[i].price<<","<<(it->second)[i].quantity<<","<<(it1->second)[i].ordertype
                                    <<","<<(it1->second)[i].orderid<<endl;
                                    (it1->second)[j].quantity=0;
                                    (it->second)[i].quantity=0;
                                    mapquantity[(it1->second)[j].orderid]=0;
                                    mapquantity[(it->second)[i].orderid]=0;
                                    i++;
                                    j++;
                            }
                        }
                        else
                            break;
                    }
                for(int i=0;i<(buyitem[symbolmatch]).size();i++)
                {
                    if((((buyitem[symbolmatch])[i]).ordertype)=="IOC")
                    {
                        ((buyitem[symbolmatch])[i]).quantity=0;
                        mapquantity[((buyitem[symbolmatch])[i]).orderid]=0;
                    }
                }

            for(int i=0;i<(sellitem[symbolmatch]).size();i++)
                {
                    if((((sellitem[symbolmatch])[i]).ordertype)=="IOC")
                    {
                        ((sellitem[symbolmatch])[i]).quantity=0;
                        mapquantity[((sellitem[symbolmatch])[i]).orderid]=0;
                    }
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
                 timestampmatch=convertstringtoint(s1);
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
        if(mapquantity.find(orderidcancel)==mapquantity.end() || flag=1)
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
