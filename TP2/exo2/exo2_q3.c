#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define CONSTANT_PROC 230000000

void do_work();

int main(int argc, char** argv){

    int pid = getpid();
    printf("Mon PID est : %d\n", pid);

    //Handler pour le signal SIGUSR1
    if(signal(SIGUSR1, do_work) == SIG_ERR){
        exit(EXIT_FAILURE);
    }

    //Mise en attente du signal
    int signal_received = pause();

    //Reception du signal
    if(signal_received == -1){
        perror("pause");
        return -1;
    }

    return 0;
}

void do_work()
{
    unsigned int nb_secondes = 1u;
    unsigned int i = CONSTANT_PROC * nb_secondes;

    while(i>0)
    {
        asm volatile("nop");
        i--;
    }
}