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

void* eat_think(int i){
	char name='A'+i;

	//chopsticks number
	int left = (i-1)%5;
	int right = i;

	if(left==-1) left=5;

	while(1){
		//think
		usleep(5);
		//get chop
		pthread_mutex_lock(&chop[left]);
		//if right chop has been taken, put down left chop.
		if(pthread_mutex_trylock(&chop[right]) == EBUSY){
			pthread_mutex_unlock(&chop[left]);
			continue;
		}
		pthread_mutex_lock(&chop[right]);

		//eat
		usleep(5);
		//put down chop
		pthread_mutex_unlock(chop[left]);
		pthread_mutex_unlock(chop[right]);
	}
}

int main(){
	pthread_mutex_t philos[5];

	int i;
	for(i=0;i<5;i++) pthread_mutex_init(&chop[i], NULL);

	//create philosphers thread
	for(i=0;i<5;i++) pthread_create(&philos[i], NULL, eat_think, i);
	
	for(i=0;i<5;i++) pthread_join(&philos[i], NULL);

	return 0;
}
