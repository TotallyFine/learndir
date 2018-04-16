## 概念

### 计算图
TensorFlow首先要定义神经网络的结构，然后再把数据放入结构中去运算。tf采用数据流来计算，所以我们首先创建一个数据流图数据以张量的形式存在。在图中结点表示数学操作，图中的线表示在结点间相互联系的多维张量。

### 例子
```python
import tensorflow as tf
import numpy as np

# create data
x_data = np.random.rand(100).astype(np.float32)
y_data = x_data*0.1 + 0.3

# 搭建模型
Weights = tf.Variable(tf.random_uniform([1], -1.0, 1.0))
biases = tf.Variable(tf.zeros[1])
y = Weights*x_data + biases

# 计算误差
loss = tf.reduce_mean(tf.square(y-y_data))

# 反向传播
optimizer = tf.train.GradientDescentOptimizer(0.5)
train = optimizer.minimize(loss)

# 训练，训练之前需要对Variable进行初始化
init = tf.global_variable_initializer()

# 创建Session，用Session来执行init初始化，并用Session来run每一次training的数据，逐步提升神经网络的预测准确性
sess = tf.Session()
sess.run(init) # 必须进行初始化
for step in range(201):
				sess.run(train)
				if step%20 == 0:
								print(step, sess.run(Weights), sess.run(biases))# 为什么输出Variable中的值的时候不是直接从里面拿，还需要session来操作？
```

### Session
Session是tf为了控制、输出文件的执行语句。运行session.run()可以获得你要得知的运算结果，或者是你所要运算的部分。

示例代码创建两个矩阵并进行相乘
```python
import tensorflow as tf

# create two matrixes
matrix1 = tf.constant([[3, 3]]) # 一行两列
matrix2 = tf.constant([[2], [2]]) # 两行一列

product = tf.matmul(matrix1, matrix2) # product并不是直接的计算步骤，所以要使用Session来激活product这个过程并得到计算结果

# 方法1
sess = tf.Session()
result = sess.run(product)
print(result) # [[12]]
sess.close()

# 方法2
with tf.Session() as sess:
    result2 = sess.run(product)
		print(result2)
```

### Variable
Variable是神经网络的参数，必须经过tf.global_variables_initalizer()。但是输入神经网络的数据可以是ndarray，这点不同于pytorch。
```python
import tensorflow as tf

state = tf.Variable(0, name='counter')

# 定义常量1
one = tf.constant(1)

# 定义加法步骤，但是并没有直接进行计算
new_value = tf.add(state, one)

# 将state更新成new-value
update = tf.assign(state, new_value)

# 定义init
init = tf.global_variables_initializer()

# 使用Session
with tf.Session() as sess:
    sess.run(init)
		for _ in range(3):
						sess.run(update)# 在执行update的时候会先计算new_value
						print(sess.run(state)) # 直接print(state)不起作用
```

### Placeholder
placeholder是tf中的占位符，暂时储存变量。tf如果想要从外部传入data，那就需要用到tf.placeholder(),然后sess.run(\*\*\*, feed\_dict={input:\*\*})
```python
import tensorflow as tf

# 在tf中需要定义的placeholder的type，一般是float32形式
input1 = tf.placeholder(tf.float32)
input2 = tf.placeholder(tf.float32)

output = tf.multiply(input1, input2)

with tf.Session() as sess:
    print(sess.run(output, feed_dict={input1:[7.], input2:[2.]}))
```
