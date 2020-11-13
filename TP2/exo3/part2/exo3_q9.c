#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define CONSTANT_PROC 57500

struct sigevent* init_sevp(struct sigevent* sevp);
struct itimerspec* init_timer_spec(struct itimerspec* new_value, unsigned int period);
void do_work_in_milliseconds(unsigned int nb_millisecondes);
timer_t get_timer_id();
void set_timer(timer_t timer_id, unsigned int period);
void build_timer(unsigned int period);
void execute_task_loop();

int main(int argc, char** argv){

    build_timer(1u);

    // Handler pour le signal SIGUSR1
    if(signal(SIGUSR1, execute_task_loop) == SIG_ERR){
        exit(EXIT_FAILURE);
    }

    while(1){
        execute_task_loop();
    }

    return 0;
}

void build_timer(unsigned int period) {
    timer_t timer_id = get_timer_id();
    set_timer(timer_id, period);
}

timer_t get_timer_id() {

    struct sigevent* sevp = (struct sigevent*)malloc(sizeof(struct sigevent));
    sevp = init_sevp(sevp);

    timer_t timer_id;

    // Creation du timer (stockage de l'ID de timer dans timer_id
    if(timer_create(CLOCK_REALTIME, sevp, &timer_id) == -1){
        perror("timer_create");
        exit(EXIT_FAILURE);
    }

    return timer_id;

}

struct sigevent* init_sevp(struct sigevent* sevp){

    sevp->sigev_notify = SIGEV_SIGNAL;
    sevp->sigev_signo = SIGUSR1;
    return sevp;

}

void set_timer(timer_t timer_id, unsigned int period) {

    struct itimerspec* timer_spec = (struct itimerspec*)malloc(sizeof(struct itimerspec));
    timer_spec = init_timer_spec(timer_spec, period);

    // Parametrage de l'intervalle et de l'instant d'expiration du timer
    if(timer_settime(timer_id, 0, timer_spec, NULL)  == -1){
        perror("timer_settime");
        exit(EXIT_FAILURE);
    }

}

struct itimerspec* init_timer_spec(struct itimerspec* new_value, unsigned int period){

    struct timespec it_interval;
    it_interval.tv_sec = period;
    it_interval.tv_nsec = 0u;

    struct timespec it_value;
    it_value.tv_sec = period;
    it_value.tv_nsec = 0u;

    new_value->it_interval = it_interval;
    new_value->it_value = it_value;
    return new_value;

}

void execute_task_loop(){
    do_work_in_milliseconds(333u);
    do_work_in_milliseconds(1000u);
    do_work_in_milliseconds(2000u);
    do_work_in_milliseconds(333u);
    do_work_in_milliseconds(1000u);
    do_work_in_milliseconds(333u);
    do_work_in_milliseconds(2000u);
    do_work_in_milliseconds(333u);
    do_work_in_milliseconds(1000u);
    do_work_in_milliseconds(333u);
    do_work_in_milliseconds(2000u);
    do_work_in_milliseconds(333u);
    do_work_in_milliseconds(1000u);
    printf("task loop done\n");
}



void do_work_in_milliseconds(unsigned int nb_millisecondes) {

    unsigned int i = CONSTANT_PROC * nb_millisecondes;

    while(i>0)
    {
        asm volatile("nop");
        i--;
    }
}