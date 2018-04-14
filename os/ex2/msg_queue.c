#include<stdio.h>
#include<unistd.h>

/*
 * 消息队列实现进程间通信
 * int msgget(key_t key, int msgflg); 
 *     key 可以认为是一个端口号，用来命名特定的消息队列，标志
 *     msgflg IPC/CREAT 若没有此队列则创建并返回一个新标识符，若已经存在则返回原来的标识符
 *            IPC/EXCL 若没有该队列则返回-1,若已经存在则返回0
 *
 * int msgrcv(int msqid, void* msgp, size_t, long msgtyp, int msgflg);
 * int msgsnd(int msqid, const void* msgp, size_t msgsz, int msglfg)
 *     msqid 消息队列的标志码
 *     msgp 指向消息缓冲区的指针，此位置用来暂存发送和接受的消息，是一个用户可定义的结构体
 *         struct msfstru{
 *           long mtype; // 消息类型必须>0
 *           char mtext[1024]; // 消息内容
 *         };
 *     msgsz 消息大小
 *     msgtyp 从消息队列内读取的消息形态，=0 代表所有消息被读取
 *     msgflg 用以控制队列中没有对应类型的消息可以接收时的处理逻辑
 *     msgsnd() 如果msgflg设置为PIC_NOWAIT 则在msgsnd()执行时若消息队列已满则msgsnd不会被阻塞，不会发信息，而是返回-1.msgflg为0时，msgsnd() msgrcv()在队列满或者空的时候阻塞等待
 *
 * int msgctl(int msgqid, ind cmd, struct msqid_ds *buf)
 *     用来设置消息队列的属性
 *     msgctl系统调用对msgqid标志的消息队列执行cmd操作，系统定义了3中操作: IPC_STAT IPC_SET IPC_RMID
 *     IPC_STAT 用来获取消息对垒对应的msgqid_ds数据结构，并将其保存到buf指定的地址空间
 *     IPC_SET 该命令用来设置消息队列的属性，要设置的属性存储在buf中
 *     IPC_RMID 从内核中删除msqid标志的消息队列
 *
 * */
