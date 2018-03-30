# coding:utf-8
from sklearn import datasets
from sklearn import svm
# 加载尾鸢花数据集
iris = datasets.load_iris()
# 加载digits数据集
digits = datasets.load_digits()
# 一个datasets类的对象像一个字典一样，.data 代表用于训练的数据 是一个n_samples n_features的array，.target代表标签
print(digits.data)
print(digits.target)
# 关于data array，无论数据是一个怎样的形式，data都是一个2D的array(n_samples, n_features)的array

# 学习和预测
# 使用digits数据集，任务是给定一个8*8的图片，预测其中是什么数字
# 在sklearn中使用fit(X, y) predict(T)
# 类sklearn.svm.SVC是支持向量分类的一个实现，接受几个超参数作为构造类的参数，我们可以把它看成是黑盒

# 这里是人为设置了超参数，但是还可以通过grid search 和 cross validation来寻找最好的超参数
clf = svm.SVC(gamma=0.001, C=100)

# 对除了最后一个数据进行训练
clf.fit(digits.data[:-1], digits.target[:-1])

# 对最后一个进行预测
print(clf.predict(digits.data[-1:]))

# 模型保存
# 可以使用pickle的方式来进行序列化，但是在sklearn中一般使用sklearn.externals import joblib
from sklearn.externals import joblib
joblib.dump(clf, 'filename.pkl')
# clf = joblib.load('filename.pkl')

# 注意事项
# 除非明确指出，用于train的的数据格式都为float64
# 用于回归的target数据会被转化成float64， 分类的target会保留原始类型

# 使用sklearn.pipeline.Pipline.set_params方法构建的模型可以重新构造超参数
import numpy as np
rng = np.random.RandomState(0)
X = rng.rand(100, 10)
y = rng.binomial(1, 0.5, 100)
X_test = rng.rand(5, 10)
clf = svm.SVC()
clf.set_params(kernel='linear').fit(X,y)
print(clf.predict(X_test))

clf.set_params(kernel='rbf').fit(X, y)
print(clf.predict(X_test))

# 当使用multiclass classifiers，target的格式对于学习和测试的时候影响很大
from sklearn.multiclass import OneVsRestClassifier
from sklearn.preprocessing import LabelBinarizer
X = [[1, 2], [2, 4], [4, 5], [3, 2], [3, 1]]
y = [0, 0, 1, 1, 2]
classif = OneVsRestClassifier(estimator=svm.SVC(random_state=0))
print(classif.fit(X, y).predict(X))

# 上面的例子中target是1d的，当然也可以使用2d的label，下面这一行是对标签进行二值化
y = LabelBinarizer().fit_transform(y)
print(classif.fit(X, y).predict(X))
'''
array([[1, 0, 0],
       [1, 0, 0],
       [0, 1, 0],
       [0, 0, 0],
       [0, 0, 0]])
'''
# 注意到第四行和第五行都是0，这意味着他们和上面三个种类的其中之一吻合

# 当用于训练队额target有不止一个标签的时候仍然可以进行二值化
from sklearn.preprocessing import MultiLabelBinarizer
y = [[0, 1], [0, 2], [1, 3], [0, 2, 3], [2, 4]]
y = MultiLabelBinarizer().fit_transform(y)
print(classif.fit(X, y).predict(X))

