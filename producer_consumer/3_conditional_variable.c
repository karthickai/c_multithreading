#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// Initialize
pthread_cond_t cv= PTHREAD_COND_INITIALIZER; /* conditional variable */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* mutex intializer */

// Function Prototype
void *emitter(void * args); /* emitter function intializer */
void *receiver(void * args); /* receiver function intializer */

int condition = 1;

int main() {
    pthread_t td1, td2; // Pthread variable

    // receiver thread creation
    if (pthread_create(&td1, NULL, receiver, NULL) !=0) {
		fprintf(stderr, "Unable to create receiver thread");
		exit(1);
	}
    
    // emitter thread creation
    if (pthread_create(&td2, NULL, emitter, NULL) !=0) {
		fprintf(stderr, "Unable to create emitter thread");
		exit(1);
	}

    // Main thread wait for td1 td2 thread to finish
    pthread_join(td1, NULL);
    pthread_join(td2, NULL);

    //Destroy mutex cache
    pthread_mutex_destroy(&mutex);
    //Destroy conditional variable cache
    pthread_cond_destroy(&cv);
    return 0;
}

void *emitter(void * args){
    pthread_mutex_trylock(&mutex);
    int pollingDelay = 5000;
    //sleep: wait for 5 seconds
    #ifdef _WIN32
    Sleep(pollingDelay);
    #else
    usleep(pollingDelay*1000);  /* sleep for 5 Seconds */
    #endif
    condition = 0; // condtion changed
    printf("%s\n\n", "After 5 second condtion changed and emitted signal");
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cv); /* notify receiver to receive signal */
    pthread_exit(0);

}


void *receiver(void * args){
    pthread_mutex_trylock(&mutex);
    while (condition)
    {
        pthread_cond_wait(&cv, &mutex);
    }
    printf("%s\n", "Recieved signal");
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}