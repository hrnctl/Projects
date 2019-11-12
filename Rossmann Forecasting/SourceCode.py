import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from sklearn.model_selection import train_test_split 
from copy import deepcopy
from sklearn.ensemble import RandomForestRegressor
from pandas import DataFrame
import csv
import xgboost as xgb
import operator
from datetime import datetime

#####
#ANALYZING PART
####
data = pd.read_csv("train.csv", low_memory=False)
#SALES BY DAY
fig, (ax1) = plt.subplots(1,1,figsize=(15,4))
sns.countplot(x="Open", hue="DayOfWeek", edgecolor="white", data=data, ax=ax1)
plt.savefig("Day_sales.png", bbox_inches="tight")

#AVERAGE SALES
#CREATE NECCESSARY COLOUMNS
data["Year"]  = data["Date"].apply(lambda x: int(str(x)[:4]))
data["Month"] = data["Date"].apply(lambda x: int(str(x)[5:7]))
data["Date"] = data["Date"].apply(lambda x: (str(x)[:7]))
# GROUPY TO GET MEAN AND PERCENT CHANGE
avgSales    = data.groupby("Date")["Sales"].mean()
pctChange = data.groupby("Date")["Sales"].sum().pct_change()
fig, (axis1, axis2) = plt.subplots(2,1,sharex=True, figsize=(20,10))
ax1 = avgSales.plot(legend=True,ax=axis1,marker='o', title="Average Sales")
ax1.set_xticks(range(len(avgSales)))
ax1.set_xticklabels(avgSales.index.tolist(), rotation=60)
ax2 = pctChange.plot(legend=True, ax=axis2, marker='o', rot=60, colormap="summer", title="Sales Percent Change")
vals = ax2.get_yticks()
ax2.set_yticklabels(["{:3.1f}%".format(x*100) for x in vals])
plt.savefig("SalesAvgandPctChange.png", bbox_inches="tight")


#AVG SALES
fig, (axis1, axis2) = plt.subplots(1, 2, figsize=(20,5))
sns.barplot(x="Year", y="Sales", data=data, edgecolor="black", ax=axis1)
axis1.set_ylabel("Average Sales")
sns.barplot(x="Year", y="Customers", data=data, edgecolor="black", ax=axis2)
axis2.set_ylabel("Average Customers")
plt.savefig("Avg_Customers.png", bbox_inches="tight")

#SALES AND DAYOF WEEK
fig, (axis1, axis2) = plt.subplots(1, 2, figsize=(20,5))
sns.barplot(x="DayOfWeek", y="Sales", data=data, edgecolor="black", order=[1,2,3,4,5,6,7], ax=axis1)
axis1.set_ylabel("Average Sales")
sns.barplot(x="DayOfWeek", y="Customers", data=data, edgecolor="black", order=[1,2,3,4,5,6,7], ax=axis2)
axis2.set_ylabel("Average Customers")
plt.savefig("CustomersByDay.png", bbox_inches="tight")

#CUSTOMER PER MONTH
fig, (axis1, axis2, axis3) = plt.subplots(3, 1, figsize=(15,12), sharex=False)
sns.boxplot([data["Customers"]], whis=np.inf, ax=axis1)
avgCustomer = data.groupby("Date")["Customers"].mean()
pctCustomer = data.groupby("Date")["Customers"].sum().pct_change()
ax = avgCustomer.plot(legend=True,marker='o', ax=axis2, sharex=axis3)
ax.set_xticks(range(len(avgCustomer)))
ax.set_title("Average Customer by Month")
ax = pctCustomer.plot(color='g', legend=True, marker='o', ax=axis3)
ax.set_xticks(range(len(avgCustomer)))
vals = ax.get_yticks()
ax.set_yticklabels(["{:3.1f}%".format(x*100) for x in vals])
ax.set_xticklabels(pctCustomer.index.tolist(), rotation=60)
ax.set_title("% Change of Customer by Month")
axis1.xaxis.set_visible(True)
minx = min(data["Customers"])
maxx = max(data["Customers"])
range_step = int((maxx - minx)/8)
ticklab = [0] + list(range(minx, maxx, range_step))
axis1.set_xticklabels(ticklab, visible=True)
plt.savefig("ChangeofCustomer.png", bbox_inches="tight")

#AVG SALES AND CUSTOMER BY PROMO
fig, (axis1, axis2) = plt.subplots(1, 2, figsize=(15,4))
sns.barplot(x="Promo", y="Sales", data=data, edgecolor="black", ax=axis1)
axis1.set_ylabel("Average Sales")
sns.barplot(x="Promo", y="Customers", data=data, edgecolor="black", ax=axis2)
axis2.set_ylabel("Average Customers")
plt.savefig("PromoSales.png", bbox_inches="tight")

#STATE HOLIDAY
sns.countplot(x="StateHoliday", edgecolor="black", data=data)
fig, (axis1,axis2) = plt.subplots(1, 2, figsize=(20,5))
sns.barplot(x="StateHoliday", y="Sales", data=data, edgecolor="black", ax=axis1)
axis1.set_ylabel("Average Sales")
mask = (data["StateHoliday"] != "0") & (data["Sales"] > 0)
sns.barplot(x="StateHoliday", y="Sales", data=data[mask], edgecolor="black", ax=axis2)
axis2.set_ylabel("Mean Sales")
plt.savefig("StateHoliday.png", bbox_inches="tight")

#SCHOOL HOLIDAY
sns.countplot(x="SchoolHoliday", data=data)
fig, (axis1, axis2) = plt.subplots(1, 2, figsize=(20,5))
sns.barplot(x="SchoolHoliday", y="Sales", data=data, edgecolor="black", ax=axis1)
axis1.set_ylabel("Mean Sales")
sns.barplot(x="SchoolHoliday", y="Customers", data=data, edgecolor="black", ax=axis2)
axis2.set_ylabel("Mean Customers")
plt.savefig("SchoolHoliday.png", bbox_inches="tight")



######
#RANDOM FOREST REGRESSION PART
######

#READ FILE
dataset = pd.read_csv("train.csv", low_memory=False)
store = pd.read_csv("store.csv")
test = pd.read_csv("test.csv")
#SELECT ONLY OPEN STORE AND SALES>0
dataset2 = dataset[dataset["Open"] != 0]
dataset2 = dataset2[dataset2["Sales"] > 0]
dataset2 = pd.merge(dataset2, store, on="Store")
#LIST FOR EXTRA FEATURES
weekList=[]
monthList=[]
yearList=[]
c=0
#READ EXTRA FEATURES
with open('extraFeatures.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:
        c+=1
        if c==1:
            continue
        weekList.append(int(row[0]))
        monthList.append(int(row[1]))
        yearList.append(int(row[2]))
#ADD TO DATASET
dataset2["WeekAvg"]=weekList
dataset2["MonthAvg"]=monthList
dataset2["YearAvg"]=yearList
dataset=dataset2.copy()
# REMOVE NANS
dataset.fillna(0, inplace=True)
dataset.loc[dataset.Open.isnull(), "Open"] = 1
#SOME FEATURES CONSIST OF A B C D MAPPING THEM
mapp = {'0':0, 'a':1, 'b':2, 'c':3, 'd':4}
dataset.StoreType.replace(mapp, inplace=True)
dataset.Assortment.replace(mapp, inplace=True)
dataset.StateHoliday.replace(mapp, inplace=True)
#SPLIT DATETIME
dataset["Date"] = pd.to_datetime(dataset["Date"], errors="coerce")
dataset["Year"] = dataset.Date.dt.year
dataset["Month"] = dataset.Date.dt.month
dataset["Day"] = dataset.Date.dt.day
dataset["DayOfWeek"] = dataset.Date.dt.dayofweek
dataset["WeekOfYear"] = dataset.Date.dt.weekofyear
#CALCULATE OPEN TIME BY THE VALUE OF MONTHS
dataset["CompetitionOpen"] = 12 * (dataset.Year - dataset.CompetitionOpenSinceYear) + (dataset.Month - dataset.CompetitionOpenSinceMonth)
#PROMO OPEN BY THE VALUE OF MONTHS
dataset["PromoOpen"] = 12 * (dataset.Year - dataset.Promo2SinceYear) +(dataset.WeekOfYear - dataset.Promo2SinceWeek) / 4.0
dataset["PromoOpen"] = dataset.PromoOpen.apply(lambda x: x if x > 0 else 0)
dataset.loc[dataset.Promo2SinceYear == 0, "PromoOpen"] = 0
# COMPARE SALES AND PROMO INTERVAL
dataset.loc[dataset.PromoInterval == 0, "PromoInterval"] = ''
dataset["IsPromoMonth"] = 0
for interval in dataset.PromoInterval.unique():
    if interval != '':
        for month in interval.split(','):
            dataset.loc[(dataset.PromoInterval == interval), "IsPromoMonth"] = 1
dataset2 = dataset.copy()
#DEEPCOPY FUNCTION
def Make_X_y(data, col="y"):
    y = data[col].as_matrix()
    X = deepcopy(data)
    del X[col]
    X = X.as_matrix()
    X, X_v, y, y_v = train_test_split(X, y, test_size=0.2, random_state=8)
    return X, y, X_v, y_v
#DROP CUSTOMERS AND DATE UNNECESSARY
dataset2 = dataset2.drop("Customers", axis=1)
dataset2= dataset2.drop("Date",axis=1)
#MAKE IT AS CATEGORY OBJECT
dataset2["PromoInterval"] = dataset2["PromoInterval"].astype("category")
#GET COLOUNM MAP IT CONVERT TO INT
cat_columns = dataset2.select_dtypes(["category"]).columns
dataset2[cat_columns] = dataset2[cat_columns].apply(lambda x: x.cat.codes)
dataset2[cat_columns] = dataset2[cat_columns].astype("int64")
features_list = dataset2.drop("Sales", axis=1).columns.values
#SPLIT DATA INTO SETS -> TEST AND VALIDATION
X, y, X_v, y_v = Make_X_y(dataset2, col="Sales")
#REGRESSION
rf_reg = RandomForestRegressor(n_jobs=-1, random_state=8)
rf_reg.fit(X, y)
#FEATURES
features = rf_reg.feature_importances_
feature_importance = DataFrame(list(reversed(sorted(zip(features, features_list)))))
#FEATURE IMPORTANCE TABLE
fig, ax = plt.subplots(1, 1, figsize=(15,8))
sns.barplot(x=0, y=1, color="salmon", data=feature_importance, edgecolor="black")
plt.xlabel("Relative Feature Importance")
plt.ylabel("Features")
plt.title("Feature Importance")
plt.savefig("Feature_Importance.png", bbox_inches="tight")
def Error_Rate(y_true, y_pred):
    data = []
    for i in range(len(y_true)):
        data.append(abs(y_true[i] - y_pred[i]))

    return np.asarray(data)
#PREDICTION CALCULATE
y_pred = rf_reg.predict(X_v)
pred_dist = Error_Rate(y_v, y_pred)
#RMSPE FUNCTION
def RMSPE(y,yhat):
    assert len(y)==len(yhat)
    
    yhat[yhat<=0]=0
    
    summ=0
    c=0
    for pair in zip(y,yhat):
    
        fraction=(y-yhat)/y
    
        fraction_squared=fraction**2
        summ+=fraction_squared[c]
        c+=1
    error=np.sqrt((1/len(yhat))*summ)
    
    return error
hata=RMSPE(y_v,y_pred)
print("RMSPE Error: %f"%hata)
print(hata)

#####
#XGBOOST KISMI
####
#XGBOOST KISMI
weekList=[]
monthList=[]
yearList=[]
c=0
with open('extraFeatures.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:
        c+=1
        if c==1:
            continue
        weekList.append(int(row[0]))
        monthList.append(int(row[1]))
        yearList.append(int(row[2]))
#DATA CLEANING
def dataClean(features, dataset):
    #Removing NaNs
    dataset.fillna(0, inplace=True)
    #If store's open is null make it 1
    dataset.loc[dataset.Open.isnull(), 'Open'] = 1
    #EXTEND FEATURES
    features.extend(['Store', 'CompetitionDistance', 'Promo', 'Promo2', 'SchoolHoliday'])
    #MAPPING A B C D TO 1 2 3 4
    features.extend(['StoreType', 'Assortment', 'StateHoliday'])
    mappings = {'0':0, 'a':1, 'b':2, 'c':3, 'd':4}
    dataset.StoreType.replace(mappings, inplace=True)
    dataset.Assortment.replace(mappings, inplace=True)
    dataset.StateHoliday.replace(mappings, inplace=True)
    features.extend(['DayOfWeek', 'Month', 'Day', 'Year', 'WeekOfYear'])
    dataset['Year'] = dataset.Date.dt.year
    dataset['Month'] = dataset.Date.dt.month
    dataset['Day'] = dataset.Date.dt.day
    dataset['DayOfWeek'] = dataset.Date.dt.dayofweek
    dataset['WeekOfYear'] = dataset.Date.dt.weekofyear
    features.extend(['WeekAvg','MonthAvg','YearAvg'])
    
    #CALCULATING COMPETITION TIME AND PROMO OPEN TIME BY MONTH
    features.append('CompetitionOpen')
    dataset['CompetitionOpen'] = 12 * (dataset.Year - dataset.CompetitionOpenSinceYear) + \
        (dataset.Month - dataset.CompetitionOpenSinceMonth)
    features.append('PromoOpen')
    dataset['PromoOpen'] = 12 * (dataset.Year - dataset.Promo2SinceYear) + \
        (dataset.WeekOfYear - dataset.Promo2SinceWeek) / 4.0
    dataset['PromoOpen'] = dataset.PromoOpen.apply(lambda x: x if x > 0 else 0)
    dataset.loc[dataset.Promo2SinceYear == 0, 'PromoOpen'] = 0
    #CHECK WHETHER IT PROMO MONTH
    features.append('IsPromoMonth')
    monthToString = {1:'Jan', 2:'Feb', 3:'Mar', 4:'Apr', 5:'May', 6:'Jun', \
             7:'Jul', 8:'Aug', 9:'Sept', 10:'Oct', 11:'Nov', 12:'Dec'}
    dataset['monthStr'] = dataset.Month.map(monthToString)
    dataset.loc[dataset.PromoInterval == 0, 'PromoInterval'] = ''
    dataset['IsPromoMonth'] = 0
    for interval in dataset.PromoInterval.unique():
        if interval != '':
            for month in interval.split(','):
                dataset.loc[(dataset.monthStr == month) & (dataset.PromoInterval == interval), 'IsPromoMonth'] = 1

    return dataset
#FEATURE MAP
def createFeatureMap(features):
    outfile = open('XGBfeatureMap.fmap', 'w')
    for i, feat in enumerate(features):
        outfile.write('{0}\t{1}\tq\n'.format(i, feat))
    outfile.close()
#RMSPE
def rmspe(y, yhat):
    return np.sqrt(np.mean((yhat/y-1) ** 2))
def rmspe_xg(yhat, y):
    y = np.expm1(y.get_label())
    yhat = np.expm1(yhat)
    return "rmspe", rmspe(y,yhat)
print("Reading files... ")
types = {'CompetitionOpenSinceYear': np.dtype(int),
         'CompetitionOpenSinceMonth': np.dtype(int),
         'StateHoliday': np.dtype(str),
         'Promo2SinceWeek': np.dtype(int),
         'SchoolHoliday': np.dtype(float),
         'PromoInterval': np.dtype(str)}
trainSet = pd.read_csv("train.csv", parse_dates=[2], dtype=types)
testSet = pd.read_csv("test.csv", parse_dates=[3], dtype=types)
storeSet = pd.read_csv("store.csv")
#FILL NANS
trainSet.fillna(1, inplace=True)
testSet.fillna(1, inplace=True)
#OPEN AND STORES HAS SALES
trainSet = trainSet[trainSet["Open"] != 0]
trainSet = trainSet[trainSet["Sales"] > 0]
#JOIN TRAIN AND TEST
trainSet = pd.merge(trainSet, storeSet, on='Store')
testSet = pd.merge(testSet, storeSet, on='Store')
trainSet['WeekAvg']=weekList
trainSet['MonthAvg']=monthList
trainSet['YearAvg']=yearList


#APPLY DATA CLEAN TO FILES
features = []
dataClean(features, trainSet)
dataClean([], testSet)
print('DATA CLEANED')
#parameters
params = {"objective": "reg:linear",
          "booster" : "gbtree",
          "eta": 0.3,
          "max_depth": 10,
          "subsample": 0.9,
          "colsample_bytree": 0.7,
          "silent": 1,
          "seed": 1301,
          "learning_rate":0.02
          }
num_boost_round = 200
print("TRAIN XGB MODEL")
trainX, validX = train_test_split(trainSet, test_size=0.012, random_state=10)
train_y = np.log1p(trainX.Sales)
valid_y = np.log1p(validX.Sales)
D_train = xgb.DMatrix(trainX[features], train_y)
D_valid = xgb.DMatrix(validX[features], valid_y)

watchlist = [(D_train, 'train'), (D_valid, 'eval')]
gbm = xgb.train(params, D_train, num_boost_round, evals=watchlist,early_stopping_rounds=100, feval=rmspe_xg, verbose_eval=True)
print("Validating...")
yhat = gbm.predict(xgb.DMatrix(validX[features]))
error = rmspe(validX.Sales.values, np.expm1(yhat))
print('RMSPE: {:.6f}'.format(error))
#PREDICTION ON TEST
dtest = xgb.DMatrix(testSet[features])
test_probs = gbm.predict(dtest)
#SUBMISSION
result = pd.DataFrame({"Id": testSet["Id"], 'Sales': np.expm1(test_probs)})
result.to_csv("Submission.csv", index=False)
#FEATURE IMPORTANCE
createFeatureMap(features)
importance = gbm.get_fscore(fmap='XGBfeatureMap.fmap')
importance = sorted(importance.items(), key=operator.itemgetter(1))
df = pd.DataFrame(importance, columns=['feature', 'fscore'])
df['fscore'] = df['fscore'] / df['fscore'].sum()
featp = df.plot(kind='barh', x='feature', y='fscore', legend=False, figsize=(6, 10))
plt.title('XGB FEATURE IMPORTANCE')
plt.xlabel('RELATIVE IMPORTANCE')
fig_featp = featp.get_figure()
fig_featp.savefig('FImportance.png', bbox_inches='tight', pad_inches=1)

'''
trainSet = pd.DataFrame(data = y_train)
trainSet['Prediction']=yhat
trainSet = pd.merge(X_train,train, left_index= True, right_index=True)
trainSet['Ratio'] = train.Prediction/train.Sales
trainSet['Error'] =abs(train.Ratio-1)
trainSet['Weight'] = train.Sales/train.Prediction
trainSet.head()
col_1 = ['Sales','Prediction']
col_2 = ['Ratio']
random=np.random.randint( low=1,high = 1115, size = 3 ) 
print(format(train.Ratio.mean()))
for i in random:
    
    t1 = pd.DataFrame(train[train['Store']==i],columns = col_1)
    t2 = pd.DataFrame(train[train['Store']==i],columns = col_2)
    t1.plot(title = 'Gerçek ve satış değerlerinin karşılaştırılması: Mağaza No.store {}'.format(i),figsize=(12,4))
trainSet.sort_values(['Error'],ascending=False,inplace= True)
trainSet[:10]
'''

