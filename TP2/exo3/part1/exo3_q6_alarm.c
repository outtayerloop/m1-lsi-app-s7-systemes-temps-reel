#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define CONSTANT_PROC 115000

void do_work();

void process_signal();

int main(int argc, char** argv){

    //Handler pour le signal SIGALRM
    if(signal(SIGALRM, process_signal) == SIG_ERR){
        exit(EXIT_FAILURE);
    }

    alarm(1u);

    while(1){}

    return 0;
}

void process_signal(){
    do_work();
    alarm(1u);
}

void do_work() {

    unsigned int nb_millisecondes = 500u;
    unsigned int i = CONSTANT_PROC * nb_millisecondes;

    while(i>0)
    {
        asm volatile("nop");
        i--;
    }

    printf("Executed task for 500ms...\n");
}

