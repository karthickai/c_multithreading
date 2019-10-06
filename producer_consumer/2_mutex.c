#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // Multithreading library

#define NUM_OF_THREAD 3
#define BUFF_SIZE 3

pthread_t tid[NUM_OF_THREAD];
void *arg;
int identity[NUM_OF_THREAD];
int buf[BUFF_SIZE];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* mutex intializer */

void *check_mutex(void *arg)
{
    pthread_mutex_trylock(&mutex);
    int *val = (int *)arg;
    int id = *val;
    buf[id] = id;
    printf("%s id = %d \n", "buf updated", id);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

int main()
{
    printf("%s\n", "Mutex Basic Example");
    int i;

    for (i = 0; i < NUM_OF_THREAD; i++)
    {
        identity[i] = i;
        pthread_create(&tid[i], NULL, check_mutex, &identity[i]);
    }

    for (i = 0; i < NUM_OF_THREAD; i++)
    {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}