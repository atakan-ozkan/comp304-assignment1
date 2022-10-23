#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define BUFFER_SIZE 64
void driver();
char* consumer();
char* swap();
int getRandom();

struct producer_consumer
{
    char message[BUFFER_SIZE];
};

int main(int argc, char *argv[]){
    if(argc == 4){
        driver(argv[1],argv[2],argv[3]);
    }
    else{
        printf("Enter three parameter: \n1)First executable name\n2)Second number of processes \n3)Third string message");
    }
    return 0;
}
// DRIVER
void driver(char str1[],char str2[],char str3[]){
    char exec_name[BUFFER_SIZE];
    char message[BUFFER_SIZE];
    int count;
    pid_t pid;
    strcpy(exec_name,str1);
    strcpy(message,str3);
    count =atoi(str2);
    if(count<2){
        printf("Number of processess must be higher or equal to 2!");
        return;
    }
    for(int n=0;n<count;n++){
        if((pid=fork())<0)
        {
            printf("Error occured during fork!\n");
            exit(0);
        }
        else if(pid ==0){          
                printf("Child %d: %s\n",n,message);
                consumer(n,exec_name,message);
        }
        else{
            kill(getpid(),SIGKILL);
        }
    }
    if(pid==0){
        printf("Parent: Playing Chinese whisper with %d processes.\n",count);
        wait(NULL);

    }
}
//CONSUMER - PRODUCER
char* consumer(int n,char* exec_name,char* message){
    struct producer_consumer *sharedMemory= {message=message};
    
    if(!strcmp(exec_name,"consumer-producer program")){
        char str[BUFFER_SIZE];
        sprintf(str, "%d", n);
        char msg[BUFFER_SIZE];
        strcpy(msg,sharedMemory->message);
        strcpy(message,swap(msg));
    }
    return sharedMemory->message;
}


char* swap(char* str){
    int length= strlen(str);
    int first= getRandom(0,length,length);
    int second = getRandom(0,length,length);
    char c;
    c= str[first];
    str[first]=str[second];
    str[second]=c;
    return str;
}
int getRandom(int lower, int upper,
                            int count)
{
    int i;
    int num;
    for (i = 0; i < count; i++) {
        num = (rand() %
        (upper - lower + 1)) + lower;
    }
    return num;
}
