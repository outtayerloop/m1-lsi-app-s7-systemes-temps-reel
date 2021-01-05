#include <stdio.h>

#define CONSTANT_PROC 710000000

void do_work_in_milliseconds(unsigned int milliseconds);
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