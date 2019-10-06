#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

// Initialize
pthread_cond_t prod_cv = PTHREAD_COND_INITIALIZER; /* producer conditional variable */
pthread_cond_t cons_cv = PTHREAD_COND_INITIALIZER; /* consumer conditional variable */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* mutex intializer */

// Function Prototype
void *producer(void * args); /* producer function intializer */
void *consumer(void * args); /* consumer function intializer */

// Global variable
#define BUF_SIZE 5
int buf[BUF_SIZE]; /* int buf array size of BUF_SIZE */
int add = 0; 	   /* pointing to add next element in buf array */
int del = 0;    /* pointing to delete next element in buf array */
int num =0;        /* number of elements in buf array */



int main() {
	pthread_t td1, td2; // pthread variable

    // producer thread creation
    if (pthread_create(&td1, NULL, producer, NULL) !=0) {
		fprintf(stderr, "Unable to create producer thread");
		exit(1);
	}
    // consumer thread creation
    if (pthread_create(&td2, NULL, consumer, NULL) !=0) {
		fprintf(stderr, "Unable to create consumer thread");
		exit(1);
	}
    // Main thread wait for td1 td2 thread to finish
    pthread_join(td1, NULL);
    pthread_join(td2, NULL);

    //Destroy mutex cache
    pthread_mutex_destroy(&mutex);
    //Destroy conditional variable cache
    pthread_cond_destroy(&prod_cv);
    pthread_cond_destroy(&cons_cv);

    return 0;
}


void *producer(void * args){
	// add element in buff for twenty times
	int i =0;
	for(i=0; i < 20; i++){
		pthread_mutex_lock(&mutex);
		
		if ( num > BUF_SIZE) {
			exit(1); /* over flow */
		}

		while (num == BUF_SIZE) {
			pthread_cond_wait(&prod_cv, &mutex); /* wait until buff array will free */
		}

		buf[add] = i;
		add = (add + 1) % BUF_SIZE; /* point next element with index BUF_SIZE */
		num++; // increment the number of element added in array

		pthread_mutex_unlock(&mutex); 

		pthread_cond_signal(&cons_cv); /* notify consumer to consume added element*/
		printf("producer inserted buf[%d]=%d\n", add, i);
		fflush(stdout);
	}
		printf("producer exit\n");
		fflush(stdout);
		pthread_exit(0);
}


void *consumer(void * args){
	int val;
	while(1) { /* loop continously*/
		pthread_mutex_lock(&mutex);

		if (num < 0) {
			exit(0); /*buf array under flow*/
		}

		while (num == 0)
		{
			pthread_cond_wait(&cons_cv, &mutex);
		}
		
		val = buf[del];
		del = (del + 1) % BUF_SIZE;
		num--;
		pthread_mutex_unlock(&mutex); 
		pthread_cond_signal(&prod_cv); /* notify consumer to consume added element*/
		printf("consumer deleted  buf[%d]=%d\n", del, val);
		fflush(stdout);
	}

}