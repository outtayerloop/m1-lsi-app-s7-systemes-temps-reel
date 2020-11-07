#include <stdio.h>
#include <unistd.h>

#define CONSTANT_PROC 770000

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

    unsigned int nb_millisecondes = 500u;
    unsigned int i = CONSTANT_PROC * nb_millisecondes;

    while(i>0)
    {
        asm volatile("nop");
        i--;
    }
}

