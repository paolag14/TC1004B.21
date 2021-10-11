#include <stdio.h>
#include <unistd.h>
#include <signal.h>

//programa que no puedes matar con ctrl c

//funcion para reemplazar cuando reciba esa señal
void handleTerm(int signal){
    printf("Recibí señal %d\b", signal);
}


int main(){
    //para registrar la señal
    signal(2, handleTerm);
    while(1){
        printf("Trabajando \n");
        //para no saturar pantalla
        sleep(1);
    }

    return 0;
}