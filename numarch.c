#include <stdio.h>
#include <unistd.h>

int main(){
    int fd[2];
    int pid;
    pipe(fd);
    pid = fork();
    if (pid == 0){
        //cerrar entrada de estandar
        close (0);
        //cerrar entrada del pipe
        dup(fd[0]);
        //cerrar salida del pipe
        close(fd[1]);
        // conectar entrada pipe
        execlp("wc", "wc", "-l", NULL);
    }
    else {
        //cerrar salida estándar
        close (1);
        //cerrar salida del pipe
        dup(fd[1]);
        //cerrar entrada del pipe
        close(fd[0]);
        // conectar salida de ls al pipe
        execlp("ls", "ls", NULL);
    }

    return 0;
}