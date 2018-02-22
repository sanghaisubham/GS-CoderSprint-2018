import pandas as pd
import numpy as np
import seaborn as sns
import warnings
from sklearn.ensemble import RandomForestRegressor
from sklearn import metrics
from sklearn.model_selection import cross_val_score,cross_val_predict
from matplotlib import pyplot
from pandas import read_csv
from pandas import set_option
from pandas.tools.plotting import scatter_matrix
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.model_selection import KFold
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from sklearn.pipeline import Pipeline
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.naive_bayes import GaussianNB
from sklearn.svm import SVC
from sklearn.ensemble import AdaBoostClassifier
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import ExtraTreesClassifier
import pandas
from sklearn import model_selection
from sklearn.ensemble import BaggingClassifier
import pandas
from sklearn import model_selection
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC
from sklearn.ensemble import VotingClassifier



warnings.filterwarnings('ignore')
%matplotlib inline
df_train=pd.read_csv('train.csv')
train_columns=df_train.columns
train_columns=train_columns[0:6]
df_train_copy=df_train
df_test= pd.read_csv('test.csv', 
                  names =train_columns)
Frame=pd.DataFrame(df_test, columns = train_columns)
# df_test=pd.read_csv('test.csv',header=None)
target=df_train['popularity']
df_train=df_train.drop('popularity',axis=1)

df_train['training_set']=1
df_test['training_set']=0
df_full=pd.concat([df_train,df_test])
(df_full.T.apply(lambda x: x.nunique(), axis=1)).sort_values(ascending=False)

from scipy.stats import iqr
q75, q25 = np.percentile(target, [75 ,25])
print(q75)
print(q25)
iqrs = iqr(target)
print("\nRange: "+str(max(target)-min(target)))
print("\nIQR: "+str(iqrs))
print("\nVariance: "+str(np.var(target)))
print("\nStandard Deviation: "+str(np.sqrt(np.var(target))))

sns.distplot(target)

# Table of survival vs. sex
Zoning = pd.crosstab(index=df_train_copy["popularity"], 
                           columns=df_train_copy["maintainence_cost"],margins=True)

ZoningPercent=Zoning.div(Zoning.ix["All"],axis=1)
ZoningPercent=ZoningPercent.T

(df_full.shape[0]-df_full.apply(lambda x: x.count(), axis=0)).sort_values(ascending=False)
((df_full.shape[0]-df_full.apply(lambda x: x.count(), axis=0))!=0).sum()
quantitative = [f for f in df_full.columns if df_full.dtypes[f] != 'object']
mean = df_full[quantitative].apply(lambda x:np.mean(x, axis=0))
sd =df_full[quantitative].apply(lambda x:np.std(x, axis=0))
MeanSD = pd.concat([mean, sd], axis=1, keys=['Mean', 'Standard Deviation'])
qualitative = [f for f in df_full.columns if f not in quantitative]
df_train=df_full[df_full['training_set']==1]
df_train=df_train.drop('training_set',axis=1)
#df_train = pd.get_dummies(df_train)
print(df_train.shape)


df_test=df_full[df_full['training_set']!=1]
df_test=df_test.drop('training_set',axis=1)
#df_test = pd.get_dummies(df_test)
#print(df_test.shape)

print(df_train.shape)
print(target.shape)
print(df_test.shape)

rf=RandomForestRegressor(n_estimators=320,n_jobs=-1)
rf.fit(df_train,target)

cv_scores =cross_val_score(rf,df_train,target,cv=5)
# Print the 5-fold cross-validation scores
print(cv_scores)
print("Average 5-Fold CV Score: {}".format(np.mean(cv_scores)))
predictions=cross_val_predict(rf,df_train,target,cv=5)
print(predictions.shape)
accuracy=metrics.r2_score(target,predictions)
print(accuracy)
preds=rf.predict(df_test)
Y=target.values
X=df_train.values
validation_size = 0.20
seed = 7
X_train, X_validation, Y_train, Y_validation = train_test_split(X, Y,
test_size=validation_size, random_state=seed)
# Test options and evaluation metric
num_folds = 10
seed = 7
# Spot-Check Algorithms
scoring = 'f1'
models = []
models.append(( ' LR ' , LogisticRegression()))
models.append(( ' LDA ' , LinearDiscriminantAnalysis()))
models.append(( ' KNN ' , KNeighborsClassifier()))
models.append(( ' CART ' , DecisionTreeClassifier()))
models.append(( ' NB ' , GaussianNB()))
results = []
names = []
for name, model in models:
    kfold = KFold(n_splits=num_folds, random_state=seed)
    cv_results = cross_val_score(model, X_train, Y_train, cv=kfold)
    results.append(cv_results)
    names.append(name)
    msg = "%s: %f (%f)" % (name, cv_results.mean(), cv_results.std())
    print(msg)


# ensembles
ensembles = []
ensembles.append(( ' AB ' , AdaBoostClassifier()))
ensembles.append(( ' GBM ' , GradientBoostingClassifier()))
ensembles.append(( ' RF ' , RandomForestClassifier()))
ensembles.append(( ' ET ' , ExtraTreesClassifier()))
results = []
names = []
for name, model in ensembles:
    kfold = KFold(n_splits=num_folds, random_state=seed)
    cv_results = cross_val_score(model, X_train, Y_train, cv=kfold)
    results.append(cv_results)
    names.append(name)
    msg = "%s: %f (%f)" % (name, cv_results.mean(), cv_results.std())
    print(msg)

seed = 7
kfold = model_selection.KFold(n_splits=10, random_state=seed)
cart = DecisionTreeClassifier()
num_trees = 100
model9 = BaggingClassifier(base_estimator=cart, n_estimators=num_trees, random_state=seed)
results = model_selection.cross_val_score(model, X_train, Y_train, cv=kfold)
print(results.mean())
model.fit(X_train,Y_train)
prediction = model.predict(X_validation)
print(accuracy_score(Y_validation, prediction))

#MAin Model

seed = 7
kfold = model_selection.KFold(n_splits=10, random_state=seed)
# create the sub models
estimators = []
model11 = BaggingClassifier()
estimators.append(('baggingclassifier', model11))
model12 = DecisionTreeClassifier()
estimators.append(('cart', model12))
model13 = ExtraTreesClassifier()
estimators.append(('ETC', model13))
# create the ensemble model
ensemble = VotingClassifier(estimators)
results = model_selection.cross_val_score(ensemble, X_train, Y_train, cv=kfold)
print(results.mean())

ensemble.fit(X_train,Y_train)
prediction = ensemble.predict(X_validation)
print(accuracy_score(Y_validation, prediction))

prediction=model.predict(df_test)
my_submission=pd.DataFrame(prediction)
my_submission.to_csv('submission_Ensemble.csv',header=None,index=False)
