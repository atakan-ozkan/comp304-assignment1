#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
void part1();
void part2();

int main(){
    //printf("---PROBLEM_1.1---\n");
    //part1();
    //printf("\n---PROBLEM_1.2---\n");
    //part2();
    return 0;
}


void part1(){
    struct timeval curr_time;
    time_t tt;
    struct tm *info;
    char buffer[64];
    int pid;
    pid =fork();

    if(pid>0){
        wait(NULL);
        printf("Child %d killed.",pid);
        kill(pid, SIGKILL);
        exit(0);
    }
    else{
        for(int a=0;a<5;a++){
            gettimeofday(&curr_time,NULL);
            tt = curr_time.tv_sec;
            info=localtime(&tt);
            printf("PID : %d, Time of Day : %s",getpid(),asctime (info));
            sleep(1);
        }
    }
}

void part2(){
    struct timeval curr_time;
    time_t tt;
    struct tm *info;
    char buffer[64];
    int pid;
    for(int a=0;a<4;a++){
        pid=fork();
        if(pid==0){
            gettimeofday(&curr_time,NULL);
            tt = curr_time.tv_sec;
            info=localtime(&tt);
            printf("PID : %d, Time of Day : %s",getpid(),asctime (info));
            sleep(1);
        }
        else{
            wait(NULL);
            printf("Child %d killed.\n",pid);
            kill(pid, SIGKILL);
            exit(0);
        }
    }
}
