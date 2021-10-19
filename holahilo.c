#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 1000
int saldo;
pthread_mutex_t saldoLock = PTHREAD_MUTEX_INITIALIZER;

/*
void * printHola(void *arg){
    printf("Hola desde el hilo\n");
    pthread_exit(NULL);
}
*/

void * suma100(void *arg){
    int localsaldo;
    pthread_mutex_lock(&saldoLock);
    localsaldo = saldo;
    localsaldo += 100;
    saldo = localsaldo;
    pthread_mutex_unlock(&saldoLock);
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[NUM_THREADS];
    saldo = 0;
    for(int i = 0; i < NUM_THREADS; i ++){
        //pthread_create(&threads[i],NULL,printHola,NULL);
        pthread_create(&threads[i],NULL,suma100,NULL);
    }

    for(int i = 0; i < NUM_THREADS; i ++){
        pthread_join(threads[i], NULL);
    }
    printf("Saldo final %d\n", saldo);
    pthread_exit(NULL);
}