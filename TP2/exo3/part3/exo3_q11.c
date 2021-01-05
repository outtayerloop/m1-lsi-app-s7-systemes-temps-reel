#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUMBER 3
#define P(x) sem_wait(x)
#define V(x) sem_post(x)
#define CONSTANT_PROC 230000000
#define SEMAPHORE_T2 (sem_t*)semaphores
#define SEMAPHORE_T3 (sem_t*)semaphores+1
#define SEMAPHORE_T4 (sem_t*)semaphores+2

pthread_t* init_threads(sem_t* semaphores);
void init_semaphores(sem_t* semaphores);
pthread_t* get_threads(sem_t* semaphores);
void await_threads(pthread_t* threads);
void* handle_task_2(void* semaphores);
void* handle_task_3(void* semaphores);
void* handle_task_4(void* semaphores);
void T2();
void T3();
void T4();
void lock_semaphore(sem_t* semaphore);
void release_semaphore(sem_t* semaphore);
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
    if(pthread_create(threads, NULL, &handle_task_2, (void*)semaphores) != 0){
        printf("pthread_create error\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(threads + 1, NULL, &handle_task_3, (void*)semaphores) != 0){
        printf("pthread_create error\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(threads + 2, NULL, &handle_task_4, (void*)semaphores) != 0){
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

void* handle_task_2(void* semaphores){
    while(1){
        T2();
        release_semaphore(SEMAPHORE_T3);
        lock_semaphore(SEMAPHORE_T2);
        T2();
        release_semaphore(SEMAPHORE_T3);
        lock_semaphore(SEMAPHORE_T2);
        T2();
        release_semaphore(SEMAPHORE_T4);
        lock_semaphore(SEMAPHORE_T2);
        T2();
        release_semaphore(SEMAPHORE_T3);
        lock_semaphore(SEMAPHORE_T2);
        T2();
        release_semaphore(SEMAPHORE_T4);
        lock_semaphore(SEMAPHORE_T2);
        T2();
        release_semaphore(SEMAPHORE_T3);
        lock_semaphore(SEMAPHORE_T2);
    }
    return NULL;
}

void* handle_task_3(void* semaphores){
    while(1){
        lock_semaphore(SEMAPHORE_T3);
        T3();
        release_semaphore(SEMAPHORE_T4);
        lock_semaphore(SEMAPHORE_T3);
        T3();
        release_semaphore(SEMAPHORE_T2);
        lock_semaphore(SEMAPHORE_T3);
        T3();
        release_semaphore(SEMAPHORE_T2);
        lock_semaphore(SEMAPHORE_T3);
        T3();
        printf("task loop done\n");
        release_semaphore(SEMAPHORE_T2);
        lock_semaphore(SEMAPHORE_T3);
    }
    return NULL;
}

void* handle_task_4(void* semaphores){
    while(1){
        lock_semaphore(SEMAPHORE_T4);
        T4();
        release_semaphore(SEMAPHORE_T2);
        lock_semaphore(SEMAPHORE_T4);
        T4();
        release_semaphore(SEMAPHORE_T2);
        lock_semaphore(SEMAPHORE_T4);
        T4();
        release_semaphore(SEMAPHORE_T2);
        lock_semaphore(SEMAPHORE_T4);
    }
    return NULL;
}

void T2(){
    do_work_in_milliseconds(333u);
}

void T3(){
    do_work_in_milliseconds(1000u);
}

void T4(){
    do_work_in_milliseconds(2000u);
}

void lock_semaphore(sem_t* semaphore){
    if(P(semaphore) == -1){
        perror("sem_wait");
        exit(EXIT_FAILURE);
    }
}

void release_semaphore(sem_t* semaphore){
    if(V(semaphore) == -1){
        perror("sem_post");
        exit(EXIT_FAILURE);
    }
}

void do_work_in_milliseconds(unsigned int milliseconds) {

    unsigned int i = CONSTANT_PROC * (unsigned int)(milliseconds / 1000);

    while(i>0)
    {
        asm volatile("nop");
        i--;
    }
}