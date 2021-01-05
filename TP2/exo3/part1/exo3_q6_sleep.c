#include <stdio.h>
#include <unistd.h>

#define CONSTANT_PROC 355000000

void do_work();

int main(int argc, char** argv){

    while(1){
        printf("Executing task for 500ms...\n");
        sleep(1u);
        do_work();
    }

    return 0;
}

void do_work() {

    unsigned int seconds = 1u;
    unsigned int i = CONSTANT_PROC * seconds;

    while(i>0)
    {
        asm volatile("nop");
        i--;
    }
}

