# coding:utf-8
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data

def compute_accury(sess, prediction, v_xs, v_ys):
    y_pre = sess.run(prediction, feed_dict={xs:v_xs})
    correct_prediciton = tf.equal(tf.argmax(y_pre, 1), tf.argmax(v_ys, 1))
    accury = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
    result = sess.run(accury, feed_dict={xs:v_xs, ys:v_ys})
    return result

def add_layer(inputs, in_size, out_size, activation_function=None):
    Weights = tf.Variable(tf.random_normal([in_size, out_size]))
    biases = tf.Variable(tf.zeros([1, out_size]) + 0.1) # tf中的bias不推荐为0
    Wx_plus_b = tf.matmul(inputs, Weights) + biases # 计算结果 y = W*x+b

    if activation_function is None:
        outputs = Wx_plus_b
    else:
        outputs = activation_function(Wx_plus_b)
    return outputs

# mnist一张28×28 784个像素
mnist = input_data.read_data_sets('MNIST_data', one_hot=True)

xs = tf.placeholder(tf.float32, [None, 784]) # 28*28
ys = tf.placeholder(tf.float32, [None, 10]) # 0-9

# 只有输出层和输入层
prediction = add_layer(xs, 784, 10, activation_function=tf.nn.softmax)

# loss函数用交叉熵，交叉熵用来衡量预测值和真实值之间的相似程度
cross_entropy = tf.reduce_mean(-tf.reduce_sum(ys*tf.log(prediction),
    reduction_indices=[1]))

train_step = tf.train.GradientDescentOptimizer(0.5).minimize(cross_entropy)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    for i in range(10):
        batch_xs, batch_ys = mnist.train.next_batch(100)
        sess.run(train_step, feed_dict={xs:batch_xs, ys:batch_ys})
        if i%2 == 0:
            print(compute_accury(mnist.test.images, mnist.test.labels))


