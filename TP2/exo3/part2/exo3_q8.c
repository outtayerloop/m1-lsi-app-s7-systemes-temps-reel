#include <stdio.h>

#define CONSTANT_PROC 115000

void do_work_in_milliseconds(unsigned int nb_millisecondes);
void execute_task_loop();

int main(int argc, char** argv){

    while(1){
        execute_task_loop();
        printf("task loop done\n");
    }

    return 0;
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
}

void do_work_in_milliseconds(unsigned int nb_millisecondes) {

    unsigned int i = CONSTANT_PROC * nb_millisecondes;

    while(i>0)
    {
        asm volatile("nop");
        i--;
    }
}