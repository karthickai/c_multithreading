#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // Multithreading library

pthread_t tid;
void *arg;

void greetings(void *arg) {
    printf("%s\n", "Thread Working");
    pthread_exit(0);
}

int main() {
    printf("%s\n", "Producer Consumer");
    int ret = pthread_create(&tid, NULL, greetings, arg);
    printf("%d\n", ret);
    ret = pthread_join(tid, NULL);
    printf("%d\n", ret);

    return 0;
}