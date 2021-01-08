#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define PROCESS_NUMBER 3

void run_main_process();
void create_all_task_named_pipes();
void create_task_named_pipe(const char* pathname);
void create_task_pipes(int task_pipes[PROCESS_NUMBER][2]);
int create_new_process();
void send_task_pid_to_parent(int task_pipe[2]);
int get_task_pid(int task_pipe[2]);
void initialize_task(int task_pipes[PROCESS_NUMBER][2], int pipe_index, void (*callback)(int));
void T2();
void T3();
void T4();
void start_tasks(int t2_pid, int t3_pid, int t4_pid);
void await_tasks();
void do_work_in_milliseconds(unsigned int milliseconds);

int main(int argc, char** argv){
    run_main_process();
    return 0;
}

void run_main_process(){
    int current_pid;
    int task_pipes[PROCESS_NUMBER][2]; // 0 = pipe de T2, 1 = pipe de T3 et 2 = pipe de T4
    create_task_pipes(task_pipes);
    setpriority(PRIO_PROCESS, getpid(), 2); // priorite de T2 = 2
    current_pid = create_new_process();
    if(current_pid == 0){
        initialize_task(task_pipes, 0, T2);
    }
    else{
        int t2_pid = get_task_pid(task_pipes[0]);
        setpriority(PRIO_PROCESS, getpid(), 3); // priorite de T3 = 3
        current_pid = create_new_process();
        if(current_pid == 0){
            initialize_task(task_pipes, 1, T3);
        }
        else{
            int t3_pid = get_task_pid(task_pipes[1]);
            setpriority(PRIO_PROCESS, getpid(), 4);  // priorite de T4 = 4
            current_pid = create_new_process();
            if(current_pid == 0){
                initialize_task(task_pipes, 2, T4);
            }
            else{
                int t4_pid = get_task_pid(task_pipes[2]);
                setpriority(PRIO_PROCESS, getpid(), 1);  // priorite du parent = 1
                start_tasks(t2_pid, t3_pid, t4_pid);
                await_tasks();
            }
        }
    }
}

void create_task_pipes(int task_pipes[PROCESS_NUMBER][2]){
    for(int i = 0; i < PROCESS_NUMBER; ++i){
        if(pipe(task_pipes[i]) == -1){
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
}

int create_new_process(){
    int pid = fork();
    if(pid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    return pid;
}

void send_task_pid_to_parent(int task_pipe[2]){
    if(close(task_pipe[0]) == -1){
        perror("close");
        exit(EXIT_FAILURE);
    }
    int task_pid = getpid();
    if(write(task_pipe[1], &task_pid, sizeof(int)) == -1){
        perror("write");
        exit(EXIT_FAILURE);
    }
    if(close(task_pipe[1]) == -1){
        perror("close");
        exit(EXIT_FAILURE);
    }
}

int get_task_pid(int task_pipe[2]){
    if(close(task_pipe[1]) == -1){
        perror("close");
        exit(EXIT_FAILURE);
    }
    int task_pid;
    if(read(task_pipe[0], &task_pid, sizeof(int)) == -1){
        perror("read");
        exit(EXIT_FAILURE);
    }
    if(close(task_pipe[0]) == -1){
        perror("close");
        exit(EXIT_FAILURE);
    }
    return task_pid;
}

void initialize_task(int task_pipes[PROCESS_NUMBER][2], int pipe_index, void (*callback)(int)){
    send_task_pid_to_parent(task_pipes[pipe_index]);
    if(signal(SIGUSR1, callback) == SIG_ERR){
        exit(EXIT_FAILURE);
    }
    pause();
}

void T2(){
    do_work_in_milliseconds(250u);
    if(kill(getpid() + 1, SIGUSR1) == -1){
        perror("kill");
        exit(EXIT_FAILURE);
    }
    while(1){
        usleep(2000000u);
        do_work_in_milliseconds(250u);
    }
}

void T3(){
    do_work_in_milliseconds(750u);
    if(kill(getpid() + 1, SIGUSR1) == -1){
        perror("kill");
        exit(EXIT_FAILURE);
    }
    while(1){
        usleep(1000000u);
        do_work_in_milliseconds(750u);
        usleep(1500000u);
        do_work_in_milliseconds(750u);
        usleep(1000000u);
        do_work_in_milliseconds(750u);
    }
}

void T4(){
    while(1){
        do_work_in_milliseconds(1500u);
        usleep(1500000u);
        do_work_in_milliseconds(1500u);
        usleep(3500000u);
        do_work_in_milliseconds(1500u);
    }
}

void start_tasks(int t2_pid, int t3_pid, int t4_pid){
    if(kill(t2_pid, SIGUSR1) == -1){
        perror("kill");
        exit(EXIT_FAILURE);
    }
}

void await_tasks(){
    for(int i = 0; i < PROCESS_NUMBER; ++i){
        if(wait(NULL) == -1){
            printf("wait error\n");
            exit(EXIT_FAILURE);
        }
    }
}

void do_work_in_milliseconds(unsigned int milliseconds){
    unsigned int i;
    if(milliseconds == 250u){
        i = 177500000; // 0.25 * CONSTANT_PROC valant 710000000
        while(i > 0)
        {
            asm volatile("nop");
            i--;
        }
    }
    else if(milliseconds == 750u){
        i = 532500000; // 0.75 * CONSTANT_PROC valant 710000000
        while(i > 0)
        {
            asm volatile("nop");
            i--;
        }
    }
    else{
        i = 1065000000; // 1.5 * CONSTANT_PROC valant 710000000
        while(i > 0)
        {
            asm volatile("nop");
            i--;
        }
    }
}

