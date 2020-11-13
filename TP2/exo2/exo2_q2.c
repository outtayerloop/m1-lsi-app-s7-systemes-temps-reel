#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_signal();

int main(int argc, char** argv){

    printf("Mon PID est : %d\n", getpid());

    //Handler pour le signal SIGUSR1
    if(signal(SIGUSR1, handle_signal) == SIG_ERR){
        exit(EXIT_FAILURE);
    }

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