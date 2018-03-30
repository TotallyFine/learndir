# coding:utf-8
# superl means supervised learning
# 当用于预测数据的类别的时候就是分类，当用于预测一个连续的值的时候就是回归
# 当进行分类的时候y是一个向量或者字符串
import numpy as np
from sklearn import datasets
iris = datasets.load_iris()
iris_X = iris.data
iris_y = iris.target
print(iris_y)
print(np.unique(iris_y))

# 使用KNN来进行分类，给定X_test的情况下，判断特征向量与每个类的相似程度
np.random.seed(0)
indices = np.random.permutation(len(iris_X))
iris_X_train = iris_X[indices[:-10]]
iris_y_train = iris_y[indices[:-10]]
iris_X_test = iris_X[indices[-10:]]
iris_y_test = iris_y[indices[-10:]]

from sklearn.neighbors import KNeighborsClassifier
knn = KNeighborsClassifier()
knn.fit(iris_X_train, iris_y_train)
print(knn.predict(iris_X_test))
print('\n')
print(iris_y_test)
