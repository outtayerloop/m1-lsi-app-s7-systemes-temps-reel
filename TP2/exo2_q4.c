#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "queue.c"

#define SIGUSR1_NUM 10
#define CONSTANT_PROC 220000

void do_work();

void process_signal();

queue_t event_queue;

int main(int argc, char** argv){

    init_queue(&event_queue);

    int pid = getpid();
    printf("Mon PID est : %d\n", pid);

    //Handler pour le signal SIGUSR1
    signal(SIGUSR1_NUM, do_work);

    while(1){
        printf("waiting for signal...\n");
        if(!is_empty(&event_queue))
            process_signal();
        pause();
    }
}

void do_work()
{
    //Detection ici dans la q5 de si la queue est vide ou pas

    push_queue(&event_queue, (int)SIGUSR1_NUM);
    process_signal();

    return;
}

void process_signal() {

    printf("received SIGUSR1\n");
    unsigned int nb_millisecondes = 2000;
    unsigned int i = CONSTANT_PROC * nb_millisecondes; //attention a ne pas utiliser un int pour eviter un overflow

    while(i>0)
    {
        asm volatile("nop");
        i--;
    }

    int is_pop_ok;
    pop_queue(&event_queue, &is_pop_ok);
}
