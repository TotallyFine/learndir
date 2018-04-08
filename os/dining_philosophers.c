#include<stdio.h>
#include<pthread.h>

/*
 * Five philosophers eat and think.
 * Let five philosophers's site be A 1 B 2 C 3 D 4 E 5 A.
 * Create A...E five thread,
 * A wait chopsticks 1 and 5,
 * B wait 1 and 2...
 * */

pthread_mutex_t chop[5];

void* eat_think(void* n){
	printf("get in to eat_think");
	int i = *(int*)n;
	char name='A'+ i;

	//chopsticks number
	int left = i;
	int right = (i+1)%5;
  int j;

	for(j=0;j<30;j++){
		//think
		sleep(5);
		printf("philosopher %s thinking...", name);
		//get chop
		pthread_mutex_lock(&chop[left]);
		//if right chop has been taken, put down left chop.
		//pthread_mutex_trylock return 0 means success
		if(pthread_mutex_trylock(&chop[right]) != 0){
			pthread_mutex_unlock(&chop[left]);
			continue;
		}
		pthread_mutex_lock(&chop[right]);

		//eat
		printf("philosopher %s eating...", name);
		sleep(5);
		//put down chop
		pthread_mutex_unlock(&chop[left]);
		pthread_mutex_unlock(&chop[right]);
	}
}

int main(){
	printf("start main()");

	pthread_t philos[5];
  
	printf("begin init mutex");
	int i;
	for(i=0;i<5;i++) pthread_mutex_init(&chop[i], NULL);
  printf("begin create thread");
	//create philosphers thread
	//pthread_create(*pthread_t t, )function's arg must be void*
	for(i=0;i<5;i++) pthread_create(&philos[i], NULL, eat_think, &i);
	printf("begin join");
	// pthread_join(pthread_t t, **arg)
	for(i=0;i<5;i++) pthread_join(philos[i], NULL);
  printf("main() finish");
	return 0;
}
