#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define MAXLEN 80 // 管道的最大长度

/*
 * 不同的进程有不同的地址空间，可以在内核中开辟一块缓冲区
 * 进程1把消息放到缓冲区中，进程2再从缓冲区中取得消息
 *
 * int pipe(int filedes[2]);
 * pipe函数在内核中开辟一块缓冲区，它有一读端和写端
 * filedes[0]只能指向管道的读端，filedes[1]只能指向管道的写端
 *
 * 所以整个实验的过程是父进程用pipe开辟管道，得到两个文件描述符指向管道的两端
 * 父进程调用fork(),子进程拥有和父进程同样的两个文件描述符
 *
 * 为了模拟两个进程之间的通信，关闭父进程中的写文件描述符，关闭子进程中的读描述符
 * */

int main(){
  int n;
	int filedes[2];
	pid_t pid1,pid2;
	char data[MAXLEN];

	if(pipe(filedes) < 0){
	  printf("error\n");
		exit(0);
	}

	if((pid1 = fork()) < 0){
	  printf("fork error\n");
		exit(1);
	}

	if(pid1 == 0){
	  // 子进程
		printf("Child Process 1 begin.\nPut in Pipe: Child Process 1 is sending a message!\n");
		strcpy(data, "Child Process 1 is sending a message!\n");
	  close(filedes[0]); // 关闭读端
  	write(filedes[1], data, strlen(data));
		printf("Child Process1 finish.\n\n");
		exit(0);
	} 
	waitpid(pid1);

	if((pid2 = fork()) < 0){
	  printf("fork error\n");
		exit(1);
	}
	if(pid2 == 0){
		printf("Child Process 2 begin.\nPut in Pipe: Child Process 2 is sending a message!\n");
	  strcpy(data, "Child Process 2 is sending a message!\n");
    close(filedes[0]);
		write(filedes[1], data, strlen(data));
		printf("Child Process 2 finish.\n\n");
		exit(0);
	}
	waitpid(pid2);
	// 父进程
	close(filedes[1]); // 关闭写端
	n = read(filedes[0], data, MAXLEN);
	printf("Father get from pipe:\n%s",data);
  return 0;
}
