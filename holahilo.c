#include <stdio.h>
#include <pthread.h>

//para correrlo gcc -o holahilo holahilo.c -lpthread
// luego ./holahilo

//variables globales
#define NUM_THREADS 1000

int saldo;
pthread_mutex_t saldoLock = PTHREAD_MUTEX_INITIALIZER;

/*
void * printHola(void *arg){
    printf("hola desde el hilo\n");
    //función que le dice al hilo que lo creó que ya terminó el hilo 
    pthread_exit(NULL);
}
*/

//región crítica
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
    //arreglo de direcciones de cada hilo
    pthread_t threads[NUM_THREADS];
    saldo = 0;
    for(int i = 0; i < NUM_THREADS; i ++){
        //tipo de planificador, propiedades del hilo, función, 
        //pthread_create(&threads[i], NULL, printHola, NULL);

        pthread_create(&threads[i], NULL, suma100, NULL);
    }

    //se tiene que esperar a que terminen todos los hilos
    for(int i = 0; i < NUM_THREADS; i ++){
        //hilos, el valor que quiero guardar del exit
        pthread_join(threads[i], NULL);
    }

    printf("Saldo final %d\n", saldo);

    //espera a que todos los hilos terminen de correr
    pthread_exit(NULL);
    //lo que a partir de aquí ya no se va a ejecutar
    
    return 0;
}