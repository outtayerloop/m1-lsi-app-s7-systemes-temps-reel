#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define P(x) pthread_mutex_lock(x)
#define V(x) pthread_mutex_unlock(x)

void* disp1(void* mutexes);
void* disp2(void* mutexes);

int main(int argc, char** argv){

    pthread_mutex_t* mutexes = (pthread_mutex_t*)malloc( 2 * sizeof(pthread_mutex_t));

    if(pthread_mutex_init(mutexes, NULL) != 0){
        perror("pthread_mutex_init m1");
        return -1;
    }

    if(pthread_mutex_init(mutexes + 1, NULL) != 0){
        perror("pthread_mutex_init m2");
        return -2;
    }

    pthread_t t1, t2;

    if(pthread_create(&t1, NULL, &disp1, (void*)mutexes) != 0){
        printf("erreur sur pthread_create pour t1\n");
        return -2;
    }

    if(pthread_create(&t2, NULL, &disp2, (void*)mutexes) != 0){
        printf("erreur sur pthread_create pour t2\n");
        return -3;
    }

    if(pthread_join(t1, NULL) != 0){
        printf("pthread_join pour t1\n");
        return -4;
    }

    if(pthread_join(t2, NULL) != 0){
        printf("pthread_join pour t2\n");
        return -5;
    }

    free(mutexes);

    return 0;
}

void* disp1(void* mutexes){

    //printf("disp1 commence\n");

    // "tu"
    printf("tu ");

    // V(mut2)
    if(V( ((pthread_mutex_t*)mutexes) + 1) == -1){
        perror("1er V(sem2) dans t1");
        exit(EXIT_FAILURE);
    }

    // P(mut1)
    if(P((pthread_mutex_t*)mutexes) == -1){
        perror("P(sem1) dans t1");
        exit(EXIT_FAILURE);
    }

    sleep(2);

    // "tes"
    printf("tes ");

    // V(mut2)
    if(V( ((pthread_mutex_t*)mutexes) + 1) == -1){
        perror("2eme V(sem2) dans t1");
        exit(EXIT_FAILURE);
    }

    return NULL;

}

void* disp2(void* mutexes){

    sleep(1);

    //printf("disp2 commence\n");

    // P(mut2)
    if(P( ((pthread_mutex_t*)mutexes) + 1) == -1){
        perror("1er P(sem2) dans t2");
        exit(EXIT_FAILURE);
    }

    // "synchronises"
    printf("synchronises ");

    // V(mut1)
    if(V((pthread_mutex_t*)mutexes) == -1){
        perror("V(sem1) dans t2");
        exit(EXIT_FAILURE);
    }

    // P(mut2)
    if(P( ((pthread_mutex_t*)mutexes) + 1) == -1){
        perror("2eme P(sem2) dans t2");
        exit(EXIT_FAILURE);
    }

    printf("threads.\n");

    return NULL;

}