#include <pthread.h>
#include  <semaphore.h>
#include <stdio.h> 

#define EATING 0
#define HUNGRY 1
#define THINKING 2
#define N 5

int status[N] = {THINKING};
sem_t s[N];
sem_t mutex;

void take_fork(int);
void put_fork(int);

void *phil(void*);

int main(){

    pthread_t threads[N];
    int phil_id [N]= {0,1,2,3,4};

    sem_init(&mutex,0,1);
    
    for(int i = 0; i < N; i++){
        sem_init(&s[i],0,0);
    }

    for(int i = 0; i < N; i++){
        pthread_create(&thread[i],NULL,phil, &phil_id[i]);
    }

    for(int i = 0; i < N; i++){
        pthread_join(threads[i],NULL);
    }

    return 0;
}

void *phil(void* id){
    int *i = id;

    while(1){
        printf("Philosopher %d is Thinking\n", *i);
        sleep(1);
        take_fork(*i);
        sleep(1);
        put_fork(*i);
    }
}

void take_fork(int id){
    sem_wait(&mutex);

    if((status[(id+4)%N] != EATING) && (status[(id+1)%N] != EATING)){
        status[id] = EATING; 
        printf("Philosopher %d is Eating\n", id);
        sem_post(&mutex);
    }else{
        status[id] = HUNGRY;
        printf("Philosopher %d is Hungry\n", id);
        sem_post(&mutex);
        sem_wait(&s[id]);
    }
}

void put_fork(int id){

    sem_wait(&mutex);

    status[i] = THINKING;

    int id_left = (id+4)%5;
    if((status[id_left] == HUNGRY) && (status[(id_left+4)%5] != EATING)){
        status[id_left] = EATING;
        sem_post(&s[id_left]);
    }
    int id_right = (id+1)%N;
    if((status[id_right] == HUNGRY) && (status[(id_right+1)%N] != EATING)){
        status[id_right] = EATING;
        sem_post(&s[id_right]);
    }
    sem_post(&mutex);
}