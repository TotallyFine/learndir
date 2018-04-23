# coding:utf-8
import os, time, random
from multiprocessing import Process, Pool, Queue

def show_fork():
    '''
    Unix/Linux系统提供了fork()系统调用，调用一次返回两次，因为对当前的进程复制了一份，所以在父进程和子进程中分别返回。
    子进程永远返回0，而父进程返回子进程的ID。一个父进程可以fork出很多的子进程，所以父进程要记下每个子进程的ID，而子进程调用getpid()就可以得到父进程的ID。
    '''
    print('Process {} start...'.format(os.getpid()))
    # only work on Unix/Linux/Mac
    pid = os.fork()
    if pid == 0:
        print('I am child process process {} and my parent is {}'.format(os.getpid(), os.getppid()))
    else:
        print('I just created a child process {}'.format(os.getpid(), pid))

def run_proc(name):# 子进程要执行的代码
    print('Run child process {} {}'.format(name, os.getpid()))

def show_multiproc():
    """
    multiprocessing 模块就是跨平台版本的多进程模块，可以在windows/Linux/mac下使用
    multiprocessing提供了一个Process类来代表一个进程对象
    """
    print('Parent process {}.'.format(os.getpid()))
    p = Process(target=run_proc, args=('test',))
    print('Process will start.')
    p.start()
    p.join()
    print('Process end.')

def show_pool():
    """
    如果要创建大量的子进程，可以用进程池的方式批量创建子进程
    """
    print('Parent process {}.'.format(os.getpid()))
    p = Pool() #p = Pool(5) 默认执行5个进程，当然可以再增加，直到close()
    for i in range(5):
        p.apply_async(long_time_task, args=(i, ))
    print('Waiting for all subprocesses done...')
    p.close() # 调用close()之后就不能呢个继续添加新的Process了
    p.join()
    print('All subprocess done.')

"""
Process之间进行通讯，操作系统提供了Queue、Pipes等多种方式来交换数据
"""
def write(q): # 写数据进程执行的代码
    for value in ['A', 'B', 'C']:
        print('Put {} to queue...'.format(value))
        q.put(value)
        time.sleep(random.random())

def read(q): # 读数据进程执行的代码
    while(True):
        value = q.get(True)
        print('Get {} from queue.'.format(value))

def show_queue():
    q = Queue() # 父进程创建Queue，并传给各个子进程
    pw = Process(target=write, args=(q,))
    pr = Process(target=read, args=(q,))
    pw.start() # 启动子进程pw，写入
    pr.start() # 启动子进程pr，读取
    pw.join()
    pr.join()
    pr.terminate() # 终止pr，因为里有死循环

if __name__ == '__main__':
    show_queue()
