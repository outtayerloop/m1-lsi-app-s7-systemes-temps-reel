/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define P(x) sem_wait(x)
#define V(x) sem_post(x)

void* disp1(void* sems);

void* disp2(void* sems);

int main(int argc, char** argv){

    sem_t* sems = (sem_t*)malloc(2 * sizeof(sem_t));

    if(sem_init(sems, 0, 0u) == -1){
        perror("sem_init sem1");
        return -1;
    }

    if(sem_init(sems + 1, 0, 0u) == -1){
        perror("sem_init sem2");
        return -1;
    }

    pthread_t t1, t2;

    if(pthread_create(&t1, NULL, &disp1, (void*)sems) != 0){
        printf("erreur sur pthread_create pour t1\n");
        return -2;
    }

    if(pthread_create(&t2, NULL, &disp2, (void*)sems) != 0){
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

    free(sems);

    return 0;
}

void* disp1(void* sems){

    //printf("disp1 commence\n");

    // "je"
    printf("je ");

    // V(sem2)
    if(V( ((sem_t*)sems) + 1) == -1){
        perror("1er V(sem2) dans t1");
        exit(EXIT_FAILURE);
    }

    // P(sem1)
    if(P((sem_t*)sems) == -1){
        perror("P(sem1) dans t1");
        exit(EXIT_FAILURE);
    }

    sleep(2);

    // "mes"
    printf("mes ");

    // V(sem2)
    if(V( ((sem_t*)sems) + 1) == -1){
        perror("2eme V(sem2) dans t1");
        exit(EXIT_FAILURE);
    }

    return NULL;

}

void* disp2(void* sems){

    sleep(1);

    //printf("disp2 commence\n");

    // P(sem2)
    if(P( ((sem_t*)sems) + 1) == -1){
        perror("1er P(sem2) dans t2");
        exit(EXIT_FAILURE);
    }

    // "synchronise"
    printf("synchronise ");

    // V(sem1)
    if(V((sem_t*)sems) == -1){
        perror("V(sem1) dans t2");
        exit(EXIT_FAILURE);
    }

    // P(sem2)
    if(P( ((sem_t*)sems) + 1) == -1){
        perror("2eme P(sem2) dans t2");
        exit(EXIT_FAILURE);
    }

    printf("threads ");

    return NULL;

}
*/
