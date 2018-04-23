# coding:utf-8
import time, threading

"""
Python 支持的是真正的Posix Thread而不是模拟出来的线程
Python的线程在被解释其执行的时候，有一个GIL锁：GLOBAL Interpreter Lock，任何python线程在执行之前都必须获得这个锁，然后每执行100条字节码，解释器就自动释放GIL锁让其他的线程有机会执行。这个GIL全局锁实际上把所有的线程上了锁，所以多线程在Python中只能交替执行，即使是100个线程跑在多个CPU上同时也只能有1个CPU被用到
GIL是Python解释器设计的历史遗留问题，通常我们使用的是官方的CPython解释器，除非使用不带GIL的解释器才可以真正使用多核
"""

def loop():
    # 获取线程的名字
    print('thread {} is running...'.format(threading.current_thread().name))
    n = 0
    while n < 5:
        n = n + 1
        print('thread {} >>> {}'.format(threading.current_thread().name, n))
        time.sleep(1)
    print('thread {} ended.'.format(threading.current_thread().name))

def show_loop():
    print('thread {} is running...'.format(threading.current_thread().name))
    t = threading.Thread(target=loop, name='LoopThread')
    t.start()
    t.join()
    print('thread {} ended.'.format(threading.current_thread().name))

balance = 0 # 银行存款
lock = threading.Lock()
def change_it(n):
    global balance
    # 先存后取应该为0
    # 但是由于没有临界锁可能会导致最后balance不是0
    x = balance + n
    balance = x
    x = balance - n
    balance = x

def run_thread(n):
    for i in range(10):
        lock.acquire() # 加锁
        try:
            change_it(n)
        finally:
            lock.release() # 释放锁

def show_lock():
    t1 = threading.Thread(target=run_thread, args=(5,))
    t2 = threading.Thread(target=run_thread, args=(8,))
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    print(balance)
if __name__ == '__main__':
    show_lock()
