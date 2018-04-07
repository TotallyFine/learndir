# coding:utf-8
import os

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

if __name__ == '__main__':
    fork()
