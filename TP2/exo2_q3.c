#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define SIGUSR1_NUM 10
#define CONSTANT_PROC 220000

void do_work();

int main(int argc, char** argv){

    int pid = getpid();
    printf("Mon PID est : %d\n", pid);

    //Handler pour le signal SIGUSR1
    signal(SIGUSR1_NUM, do_work);

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
    unsigned int nb_millisecondes = 2000;
    unsigned int i = CONSTANT_PROC * nb_millisecondes; //attention a ne pas utiliser un int pour eviter un overflow

    while(i>0)
    {
        asm volatile("nop");
        i--;
    }

    return;
}