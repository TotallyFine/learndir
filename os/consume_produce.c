#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define N 10 //缓冲区大小
#define PN 5 //生产者个数
#define CN 5 //消费者个数

int buffer[N];//商品货架，临界区资源

int in = 0;//指向的位置没有放入商品
int out = 0;//指向的位置放入了商品

sem_t empty;//empty信号量
sem_t full;//full信号量
pthread_mutex_t mutex;//临界区锁

void produce(void* arg);
void consume(void* arg);

void produce(void* arg){
  while(1){
	  sleep(1);//produce nextp
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);

		buffer[in] = 1;
		in = (in + 1)%N;

		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
}

void consume(void* arg){
  while(1){
	  int nextp;
		sem_wait(&full);
		pthread_mutex_lock(&mutex);

		nextp = buffer[out];
		out = (out + 1)%N;
    pthread_mutex_unlock(&mutex);
		sem_lock(&empty);

		sleep(2);//consume
	}
}

int main(){
  int i;
	pthread_t producer[PN];
	pthread_t consumer[CN];
	pthread_mutex_init(&mutex, NULL);//初始化
  
	if(sem_init(&empty, 0, N-1) != 0){
	  printf("empty init error\n");
		exit(0);
	}
	if(sem_init(&full, 0, 0) != 0){
	  printf("full init error\n");
		exit(0);
	}

	for(i=0;i<PN;i++){
	  if(pthread_create(&producer[i], NULL, produce, (void*)i) != 0){
		  printf("create producer error\n");
			exit(0);
		}
	}

	for(i=0;i<CN;i++){
	  if(pthread_create(&consumer[i], NULL, consume, (void*)i) != 0){
		  printf("create consumer error\n");
			exit(0);
		}
	}

	for(i=0;i<PN;i++) pthread_join(producer[i], NULL);
	for(i=0;i<CN;i++) pthread_join(consumer[i], NULL);

	return 0;
}
