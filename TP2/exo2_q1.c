#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define SIGUSR1_NUM 10

void handle_signal();

int main(int argc, char** argv){

    printf("Mon PID est : %d\n", getpid());

    //Handler pour le signal SIGUSR1
    signal(SIGUSR1_NUM, handle_signal);

    //Mise en attente du signal
    int signal_received = pause();

    if(signal_received == -1){
        perror("pause");
        return -1;
    }

    return 0;
}

void handle_signal(){
    printf("SIGUSR1 received\n");
}