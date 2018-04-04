## OS experiment

This folder is for OS experiment.

### Usage
gcc file.c, will create a.out, ./a.out can excute this file.
gcc -o hello hello.c, specify the output file.
gcc -c hello.c, only complie the code and find errors, this option will create hello.o.
After the -o, use gcc -o hello.out hello.c can run the code.

To use extrac library such pthread.h, gcc filename -lpthread.

### pthread.h
```c
int pthread__create(pthread_t* tid, const pthread_attr_t *attr, 
    void*(start_rtn)(void), void* arg);
return 0 if success else error code.

argument:
  tid: variable which point to different thread, used for function 's output.
    &tid can be used as thread ID.
  attr: used for custom thread, default is NULL.
  start_rtn: function pointer, this func can return void* other type also fine,
      catched by pthread_join().
  arg: start_rtn's args.
```
```c 
int pthread_join(pthread_t thread, void** rval_ptr);
return 0 if sucess else error code.

argument:
  thread: thread ID.
  rval_ptr: pointer which point to return pointer.
```
```c
pthread_mutex_t mutex;
```
