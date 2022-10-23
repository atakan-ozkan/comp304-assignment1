#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#define READ_END    0
#define WRITE_END    1
void part1();
void part2();

int main(){
    //printf("---PROBLEM_2.1---\n");
    //part1();
    //printf("\n---PROBLEM_2.2---\n");
    //part2();
    return 0;
}
void part1(){
    int wr1[2];
    int wr2[2];
    //wr[0] read
    //wr[1] write
    int pid1,pid2,val,output1,output2;
    
    if (pipe(wr1) == -1) {
        fprintf(stderr,"Pipe 1 failed");
        return;
    }
    if(pipe(wr2)==-1){
        fprintf(stderr,"Pipe 2 failed");
        return;
    }

    pid1=fork();
    if(pid1==0){
        int x;
        close(wr1[WRITE_END]);
        read(wr1[READ_END],&x,sizeof(int));
        close(wr1[READ_END]);
        output1=(getpid()*x);
        printf("First Child Input : %d , Output : %d * %d = %d\n",
               x,getpid(),x,output1);
    }
    else{
        pid2=fork();
        if(pid2==0){
            int x;
            close(wr2[WRITE_END]);
            read(wr2[READ_END],&x,sizeof(int));
            close(wr2[READ_END]);
            output2=(getpid()/x);
            printf("Second Child Input : %d , Output : %d / %d = %d\n",
                   x,getpid(),x,output2);
        }
        else{
            printf("Enter a number : ");
            scanf("%d",&val);
            close(wr2[READ_END]);
            close(wr1[READ_END]);
            write(wr2[WRITE_END],&val,sizeof(int));
            write(wr1[WRITE_END],&val,sizeof(int));
            close(wr1[WRITE_END]);
            close(wr2[WRITE_END]);
            wait(NULL);
            int sum=((pid1*val)+(pid2/val));
            printf("\nThe sum is : %d\n",sum);
            kill(pid1,SIGKILL);
            kill(pid2,SIGKILL);
        }
    }
}

void part2(){
    int wr1[2];
    int wr2[2];
    //wr[0] read
    //wr[1] write
    int pid1,pid2,val,output1,output2;
    
    if (pipe(wr1) == -1) {
        fprintf(stderr,"Pipe 1 failed");
        return;
    }
    if(pipe(wr2)==-1){
        fprintf(stderr,"Pipe 2 failed");
        return;
    }

    pid1=fork();
    if(pid1==0){
        sleep(5);
        int x;
        close(wr1[WRITE_END]);
        read(wr1[READ_END],&x,sizeof(int));
        close(wr1[READ_END]);
        output1=(getpid()*x);
        printf("First Child Input : %d , Output : %d * %d = %d\n",
               x,getpid(),x,output1);
    }
    else{
        pid2=fork();
        if(pid2==0){
            sleep(5);
            int x;
            close(wr2[WRITE_END]);
            read(wr2[READ_END],&x,sizeof(int));
            close(wr2[READ_END]);
            output2=(getpid()/x);
            printf("Second Child Input : %d , Output : %d / %d = %d\n",
                   x,getpid(),x,output2);
        }
        else{
            sleep(5);
            printf("Enter a number : ");
            scanf("%d",&val);
            close(wr2[READ_END]);
            close(wr1[READ_END]);
            write(wr2[WRITE_END],&val,sizeof(int));
            write(wr1[WRITE_END],&val,sizeof(int));
            close(wr1[WRITE_END]);
            close(wr2[WRITE_END]);
            wait(NULL);
            int sum=((pid1*val)+(pid2/val));
            printf("\nThe sum is : %d\n",sum);
            kill(pid1,SIGKILL);
            kill(pid2,SIGKILL);
        }
    }
}
