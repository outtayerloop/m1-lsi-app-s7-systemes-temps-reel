#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUMBER 3
#define P(x) sem_wait(x)
#define V(x) sem_post(x)
#define CONSTANT_PROC 230000000

pthread_t* init_threads(sem_t* semaphores);
void init_semaphores(sem_t* semaphores);
pthread_t* get_threads(sem_t* semaphores);
void await_threads(pthread_t* threads);
void* T2(void* semaphores);
void* T3(void* semaphores);
void* T4(void* semaphores);
void do_work_in_milliseconds(unsigned int milliseconds);

int main(int argc, char** argv){

    sem_t* semaphores = (sem_t*)malloc(THREAD_NUMBER * sizeof(sem_t));
    pthread_t* threads = init_threads(semaphores);
    await_threads(threads);

    free(semaphores);

    return 0;
}

pthread_t* init_threads(sem_t* semaphores){
    init_semaphores(semaphores);
    return get_threads(semaphores);
}

void init_semaphores(sem_t* semaphores){
    for(int i = 0; i < THREAD_NUMBER; ++i){
        if(sem_init(semaphores + i, 0, 0u) == -1){
            perror("sem_init");
            exit(EXIT_FAILURE);
        }
    }
}

pthread_t* get_threads(sem_t* semaphores){
    pthread_t* threads = (pthread_t*)malloc(THREAD_NUMBER * sizeof(pthread_t));
    if(pthread_create(threads, NULL, &T2, (void*)semaphores) != 0){
        printf("pthread_create error\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(threads + 1, NULL, &T3, (void*)semaphores) != 0){
        printf("pthread_create error\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(threads + 2, NULL, &T4, (void*)semaphores) != 0){
        printf("pthread_create error\n");
        exit(EXIT_FAILURE);
    }
    return threads;
}

void await_threads(pthread_t* threads){
    for(int i = 0; i < THREAD_NUMBER; ++i){
        if(pthread_join(threads[i], NULL) != 0){
            printf("pthread_join pour t1\n");
            exit(EXIT_FAILURE);
        }
    }
}

void* T2(void* semaphores){
    do_work_in_milliseconds(333u);
    return NULL;
}

void* T3(void* semaphores){
    do_work_in_milliseconds(1000u);
    return NULL;
}

void* T4(void* semaphores){
    do_work_in_milliseconds(2000u);
    return NULL;
}

void do_work_in_milliseconds(unsigned int milliseconds) {

    unsigned int i = CONSTANT_PROC * (unsigned int)(milliseconds / 1000);

    while(i>0)
    {
        asm volatile("nop");
        i--;
    }
}