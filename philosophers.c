#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define N 5

pthread_t thread_id[N];
pthread_mutex_t philosopher_forks[N];
int philosophers[N];

void *philosopher(void *id_philosopher);


void *philosopher(void *id_philosopher){
	int this_philosofer = *((int *) id_philosopher);
	int right_philosopher = (this_philosofer + 1) % N;
	printf("Created philosofer %d!\n",this_philosofer+1);
	sleep(2);
	while(1){
		pthread_mutex_lock(&philosopher_forks[this_philosofer]);
		pthread_mutex_lock(&philosopher_forks[right_philosopher]);
		printf("Philosofer %d eating!\n", this_philosofer+1);
		sleep(2);
		printf("Philosofer %d thinking!\n", this_philosofer+1);
		pthread_mutex_unlock(&philosopher_forks[this_philosofer]);
		pthread_mutex_unlock(&philosopher_forks[right_philosopher]);
		sleep(2);
	}
}


int main(int argc, char *argv[ ]) {
	int i;

	for(i=0;i<N;i++){
		philosophers[i] = i;
		pthread_mutex_init (&philosopher_forks[i], NULL);
      	pthread_create(&thread_id[i], NULL, philosopher, &philosophers[i]);
   	}

   	for(i=0;i<N;i++)
    	pthread_join(thread_id[i],NULL);

    return 0;
}