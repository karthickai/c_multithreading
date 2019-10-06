#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


pthread_t td1, td2; // pthread variable
pthread_cond_t prod_cv; // producer conditional variable
pthread_cond_t cons_cv; // consumer conditional variable

pthread_mutex_t mutex;

void *producer(void * args){


}


void *consumer(void * args){


}

int main() {
    // conditional variable initalization
    pthread_cond_init(&prod_cv, NULL);
    pthread_cond_init(&cons_cv, NULL);

    // mutex initalization
    pthread_mutex_init(&mutex, NULL);

    // Thread 1 created
    pthread_create(&td1, NULL, producer, 1);
    // Thread 2 created
    pthread_create(&td2, NULL, consumer, 1);

    // Main thread wait for td1 td2 thread to finish
    pthread_join(td1, NULL);
    pthread_join(td2, NULL);

    //Destroy mutex cache
    pthread_mutex_destroy(&mutex);
    //Destroy conditional variable cache
    pthread_cond_destroy(&cv);
    return 0;
}