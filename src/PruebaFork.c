
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>


struct proceso{
    unsigned int pid;
};

void forkPadre(int *p){

    (*p)++;
    printf("Hello World Padre %d: %d\n", getpid(),*p );

}

void forkHijo( int *p ){

    (*p)++;
    printf("Hello World Hijo %d: %d\n", getpid(),*p );

}

int main( int argc,char **argv ){

    //Memoria compartida ...
    int * p = (int *) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0 );

    *p = 0;

    pid_t c_pid = fork();
    if ( c_pid < 0 ){
        //ERROR...
        perror("Error al crear proceso con el Fork\n");
        exit(1);
    }
    if ( c_pid == 0){
        forkPadre( p );
    }else{
        forkHijo( p );
    }

    return 0;
}