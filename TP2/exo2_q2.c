#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define SIGUSR1_NUM 10
#define CONSTANT_PROC 220000

void do_work();

int main(int argc, char** argv){

    printf("Mon PID est : %d\n", getpid());

    //Handler pour le signal SIGUSR1
    signal(SIGUSR1_NUM, do_work);

    //Mise en attente du signal
    int signal_received = pause();

    if(signal_received == -1){
        perror("pause");
        return -1;
    }

    return 0;
}

void do_work()
{
    unsigned int nb_millisecondes = 4000;
    unsigned int i = CONSTANT_PROC * nb_millisecondes; //attention a ne pas utiliser un int pour eviter un overflow

    while(i>0)
    {
        asm volatile("nop");
        i--;
    }

    return;
}