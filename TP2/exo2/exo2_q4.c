#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "queue.c"

#define CONSTANT_PROC 770000000

void do_work();

void process_signal();

void handle_event_list();

queue_t event_queue;

int main(int argc, char** argv){

    init_queue(&event_queue);

    int pid = getpid();
    printf("Mon PID est : %d\n", pid);

    //Handler pour le signal SIGUSR1
    if(signal(SIGUSR1, process_signal) == SIG_ERR){
        exit(EXIT_FAILURE);
    }

    while(1){
        handle_event_list();
        printf("waiting for signal...\n");
        pause();
    }
}

void process_signal()
{
    push_queue(&event_queue, SIGUSR1);
}

void do_work() {

    unsigned int nb_secondes = 1u;
    unsigned int i = CONSTANT_PROC * nb_secondes;

    while(i>0)
    {
        asm volatile("nop");
        i--;
    }
}

void handle_event_list(){

    while(!is_empty(&event_queue)){
        printf("processing received SIGUSR1\n");
        do_work();
        int is_pop_ok;
        if(pop_queue(&event_queue, &is_pop_ok) == -1){
            exit(EXIT_FAILURE);
        }
    }

}