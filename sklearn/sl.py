# coding:utf-8
# sl means statistical learning,统计学习

# 数据集部分
# scikit-learn 使用一个或者多个数据集（表现为2D数组）来进行学习
from sklearn import datasets
iris = datasets.load_iris()
data = iris.data
# data.shape的第一个是样本数 第二个是样本的feature数
print(data.shape)
'''
(150, 4)
150个样本，4个feature分别为萼片sepal，花瓣petal，的长度和宽度
'''
# estimators objects
# 一个estimator可以是一个分类、回归、聚类算法或者是用于从raw data提取feature的extracts/filters

# estimator使用fit(data)方法来训练
# estimator的参数。estimator的所有参数在实例化的时候被确定
# estimator = Estimator(param1=1, param2=2)
# 可以通过print(estimator.param1)来显示参数

# 通过学习获得的参数。当训练完成的时候这些参数就确定
# print(estimator.estimated_param_)来查看
