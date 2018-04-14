#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define RN 5
#define WN 5

sem_t rmutex, wmutex;
int readcount=0;

void read_(int *);
void write_(int *);

int main(){
		int i;
		int r1=1, r2=2, r3=3, r4=4, r5=5;
		int w1=1, w2=2, w3=3, w4=4, w5=5;

    pthread_t reader[RN];
		pthread_t writer[WN];

		if(sem_init(&rmutex, 0, RN) != 0){
		    printf("rmutex init error\n");
				exit(0);
		}
		if(sem_init(&wmutex, 0, WN) != 0){
		    printf("wmutex init error\n");
				exit(0);
		}
		pthread_create(&reader[0], NULL, read_, &r1);
  	pthread_create(&reader[1], NULL, read_, &r2);
	  pthread_create(&reader[2], NULL, read_, &r3);
	  pthread_create(&reader[3], NULL, read_, &r4);
	  pthread_create(&reader[4], NULL, read_, &r5);

    pthread_create(&writer[0], NULL, write_, &w1);
  	pthread_create(&writer[1], NULL, write_, &w2);
	  pthread_create(&writer[2], NULL, write_, &w3);
	  pthread_create(&writer[3], NULL, write_, &w4);
	  pthread_create(&writer[4], NULL, write_, &w5);

		for(i=0;i<RN;i++) pthread_join(reader[i], NULL);
		for(i=0;i<WN;i++) pthread_join(writer[i], NULL);

		return 0;

}

void read_(int* n){
   int i;
	 for(i=0;i<10;i++){
			 usleep(3);
	     sem_wait(&rmutex);
			 if(readcount==0) sem_wait(&wmutex);
			 readcount++;
       sem_post(&rmutex);

			 printf("reader %d is reading...\n", *n);

			 sem_wait(&rmutex);
			 readcount--;
			 if(readcount==0) sem_post(&wmutex);
			 sem_post(&rmutex);
	 } 
}

void write_(int* n){
		int i;
    for(i=0;i<10;i++){
				usleep(5);
		    sem_wait(&wmutex);

				printf("writer %d is writing...\n", *n);

				sem_post(&wmutex);
		}
}
