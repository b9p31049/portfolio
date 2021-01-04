#!/usr/bin/env python
# coding: utf-8

# In[3]:


from sklearn import model_selection, svm, metrics

# ワインデータ(CSV)を読みこむ --- (*1)
wine_csv= []
with open("winequality-red.csv", "r", encoding="utf-8") as fp:
    no = 0
    for line in fp:
        line = line.strip() 
        cols = line.split(";")
        wine_csv.append(cols)

# 一行目はヘッダ行なので削除 --- (*2)
wine_csv = wine_csv[1:]

# CSVの各データを数値に変換 --- (*3)
labels = []
data = []
for cols in wine_csv:
    cols = list(map(lambda n: float(n), cols)) # --- (*3a)
    # ワインのグレードを調整 --- (*4)
    grade = int(cols[11]) # 末尾のデータがワインのグレード
    if grade == 9: grade = 8 # 少なすぎるサンプルを調整
    if grade < 4 : grae = 5
    labels.append(grade)
    data.append( cols[0:11] ) # ワインの成分データ --- (*5)

# 訓練用データとテスト用データに分ける --- (*6)
data_train, data_test, label_train, label_test =     model_selection.train_test_split(data, labels)

# SVMのアルゴリズムを利用して学習 --- (*7)
clf = svm.SVC()
clf.fit(data_train, label_train)

# 予測してみる --- (*8)
predict = clf.predict(data_test)

# 結果を表示する --- (*9)
ac_score = metrics.accuracy_score(label_test, predict)
cl_report = metrics.classification_report(label_test, predict)
print("正解率=", ac_score)
print("レポート=\n", cl_report)


# In[ ]:




