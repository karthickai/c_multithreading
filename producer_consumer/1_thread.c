#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // Multithreading library

#define NUM_OF_THREAD 5

pthread_t tid[NUM_OF_THREAD];
void *arg;
int i;
int identity[NUM_OF_THREAD];

void *greetings(void *arg) {
    int *val = (int*)arg;
    int id = *val;
    printf("%s id = %d \n", "Thread Started", id);
    pthread_exit(0);
}

int main() {
    printf("%s\n", "Producer Consumer");
    for(i=0; i< NUM_OF_THREAD; i++){
        identity[i] = i;
        if (pthread_create(&tid[i], NULL, greetings, &identity[i]) !=0) {
		    fprintf(stderr, "Unable to create producer thread");
		    exit(1);
	    }
    }

    for(i=0; i< NUM_OF_THREAD; i++){
        pthread_join(tid[i], NULL);
    }
    
    return 0;
}