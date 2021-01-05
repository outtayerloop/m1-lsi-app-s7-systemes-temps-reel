#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CONSTANT_PROC 355000000

#define STUDY_PERIOD 12

/**
 * Les definitions suivantes representent T2, handle_task_3 et handle_task_4.
 * T3_1_3 signifie duree d'execution d'1/3 de handle_task_3, idem pour les notations semblables.
 */

#define T2() do_work_in_milliseconds(333u)
#define T3() do_work_in_milliseconds(1000u)
#define T3_1_3() do_work_in_milliseconds(333u)
#define T3_2_3() do_work_in_milliseconds(666u)
#define T4_1_2() do_work_in_milliseconds(1000u)
#define T4_1_3() do_work_in_milliseconds(666u)
#define T4_1_6() do_work_in_milliseconds(333u)

struct sigevent* init_sevp(struct sigevent* sevp);
struct itimerspec* init_timer_spec(struct itimerspec* new_value, unsigned int period);
void do_work_in_milliseconds(unsigned int seconds);
timer_t get_timer_id();
void set_timer(timer_t timer_id, unsigned int period);
void build_timer(unsigned int period);
void empty_handler();
void handle_task_loop();
void task_loop_t0();
void task_loop_t1();
void task_loop_t2();
void task_loop_t3();
void task_loop_t4();
void task_loop_t5();
void task_loop_t6();
void task_loop_t7();
void task_loop_t8();
void task_loop_t9();
void task_loop_t10();
void task_loop_t11();

/**
 * Compteur artificiel du nombre de secondes passees.
 */
int cpt = 0;

int main(int argc, char** argv){

    build_timer(1u);

    // Handler pour le signal SIGUSR1
    if(signal(SIGUSR1, empty_handler) == SIG_ERR){
        exit(EXIT_FAILURE);
    }

    while(1){
        handle_task_loop();
        pause();
    }
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

void empty_handler(){}

void handle_task_loop(){
    if(cpt % STUDY_PERIOD == 0)
        task_loop_t0();
    else if(cpt % STUDY_PERIOD == 1)
        task_loop_t1();
    else if(cpt % STUDY_PERIOD == 2)
        task_loop_t2();
    else if(cpt % STUDY_PERIOD == 3)
        task_loop_t3();
    else if(cpt % STUDY_PERIOD == 4)
        task_loop_t4();
    else if(cpt % STUDY_PERIOD == 5)
        task_loop_t5();
    else if(cpt % STUDY_PERIOD == 6)
        task_loop_t6();
    else if(cpt % STUDY_PERIOD == 7)
        task_loop_t7();
    else if(cpt % STUDY_PERIOD == 8)
        task_loop_t8();
    else if(cpt % STUDY_PERIOD == 9)
        task_loop_t9();
    else if(cpt % STUDY_PERIOD == 10)
        task_loop_t10();
    else{
        task_loop_t11();
        printf("task loop done\n");
    }
    ++cpt;
}

/**
 * Les fonctions suivantes representent t (temps en secondes) de 0 à 11 sur la periode d'etude de 12 secs.
 */

void task_loop_t0(){
    T2();
    T3_2_3();
}

void task_loop_t1(){
    T3_1_3();
    T4_1_3();
}

void task_loop_t2(){
    T4_1_2();
}

void task_loop_t3(){
    T4_1_6();
    T2();
    T3_1_3();
}

void task_loop_t4(){
    T3_2_3();
    T2();
}

void task_loop_t5(){
    T4_1_2();
}

void task_loop_t6(){
    T4_1_2();
}

void task_loop_t7(){
    T2();
    T3_2_3();
}

void task_loop_t8(){
    T3_1_3();
    T2();
    T4_1_6();
}

void task_loop_t9(){
    T4_1_2();
}

void task_loop_t10(){
    T4_1_3();
    T2();
}

void task_loop_t11(){
    T3();
}

void do_work_in_milliseconds(unsigned int milliseconds) {
    unsigned int i;
    if(milliseconds == 333u){
        i = 236430000u; // 0.333 * CONSTANT_PROC valant 710000000
        while(i > 0)
        {
            asm volatile("nop");
            i--;
        }
    }
    else{
        i = CONSTANT_PROC * (milliseconds / 1000u);
        while(i > 0)
        {
            asm volatile("nop");
            i--;
        }
    }
}