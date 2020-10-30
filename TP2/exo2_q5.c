#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "queue.c"

#define SIGUSR1_NUM 10
#define CONSTANT_PROC 220000

void do_work();

void process_signal();

void handle_event_list();

queue_t event_queue;

int cpt = 0;

int main(int argc, char** argv){

    init_queue(&event_queue);

    int pid = getpid();
    printf("Mon PID est : %d\n", pid);

    //Handler pour le signal SIGUSR1
    signal(SIGUSR1_NUM, process_signal);

    while(1){
        handle_event_list();
        printf("waiting for signal...\n");
        pause();
    }
}

void process_signal()
{
    push_queue(&event_queue, SIGUSR1_NUM);
    if(!is_filled_with_only_one_event(&event_queue) && !is_empty(&event_queue)){
        printf("Un signal est arrive trop tot\n");
    }
    return;
}

void do_work() {

    unsigned int nb_millisecondes = 10000;
    unsigned int i = CONSTANT_PROC * nb_millisecondes; //attention a ne pas utiliser un int pour eviter un overflow

    while(i>0)
    {
        asm volatile("nop");
        i--;
    }

    int is_pop_ok;
    pop_queue(&event_queue, &is_pop_ok);
}

void handle_event_list(){
    while(!is_empty(&event_queue)){
        printf("processing received SIGUSR1\n");
        do_work();
    }
}