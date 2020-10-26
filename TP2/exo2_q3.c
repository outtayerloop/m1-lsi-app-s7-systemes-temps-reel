#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define SIGUSR1_NUM 10
#define CONSTANT_PROC 220000

void do_work();

void fork_parent();

int main(int argc, char** argv){

    int parent_pid = getpid();
    printf("Mon PID est : %d\n", parent_pid);

    //Handler pour le signal SIGUSR1
    signal(SIGUSR1_NUM, fork_parent);

    //Mise en attente du signal
    int signal_received = pause();

    //Reception du signal
    if(signal_received == -1){

        int current_pid = getpid();

        if(current_pid == -1){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        // Fils
        if(current_pid != parent_pid){
            do_work();
            exit(EXIT_SUCCESS);
        }
        // Pere
        else{
            while(wait(NULL) != -1);
            perror("pause");
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}

void fork_parent(){
    fork();
};

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