# coding:utf-8
import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt 

def add_layer(inputs, in_size, out_size, activation_function=None):
    Weights = tf.Variable(tf.random_normal([in_size, out_size]))
    biases = tf.Variable(tf.zeros([1, out_size]) + 0.1) # tf中的bias不推荐为0
    Wx_plus_b = tf.matmul(inputs, Weights) + biases # 计算结果 y = W*x+b

    if activation_function is None:
        outputs = Wx_plus_b
    else:
        outputs = activation_function(Wx_plus_b)
    return outputs

if __name__ == '__main__':
    x_data = np.linspace(-1, 1, 300, dtype=np.float32)[:, np.newaxis]
    noise = np.random.normal(0, 0.05, x_data.shape).astype(np.float32) # 给数据增加噪音
    y_data = np.square(x_data) -0.5 + noise

    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    ax_scatter(x_data, y_data)
    plt.ion() # 用于连续显示图像
    plt.show()

    # 定义占位符
    xs = tf.placeholder(tf.float32, [None, 1])
    ys = tf.placeholder(tf.float32, [None, 1])

    # 定义神经层
    # 输入层1个神经元，隐藏层10个，输出层1个神经元
    l1 = add_layer(xs, 1, 10, activation_function=tf.nn.relu)
    prediction = add_layer(l1, 10, 1, activation_function=None)
    loss = tf.reduce_mean(tf.reduce_sum(tf.square(ys - prediction),
        reduction_indices=[1]))

    # 定义optimizer
    train_step = tf.train.GradientDescentOptimizer(0.1).minimize(loss)
    
    init = tf.global_variables_initializer()

    with tf.Session() as sess:
        sess.run(init)
        for i in range(1000):
            sess.run(train_step, feed_dict={xs:x_data, ys:y_data})
            if i%50 == 0: # 每隔50次显示loss，并刷新图像
                print(sess.run(loss, feed_dict={xs:x_data, ys:y_data}))
                try:
                    ax.lines.remove(lines[0])
                expect Exception:
                    pass
                prediction_value = sess.run(prediction, feed_dict={xs:x_data})
                lines = ax.plot(x_data, prediction_value, 'r-', lw=5)
                plt.pause(0.1) # 暂停0.1s
