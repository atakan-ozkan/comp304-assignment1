#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 64
struct producer_consumer
{
    char message[BUFFER_SIZE];
};
int main(int argc, char *argv[]){
    printf("sdasdasda");
    int n;
    char message[BUFFER_SIZE];
    if(argc==3){
        n= atoi(argv[1]);
        strcpy(message,argv[2]);
        struct producer_consumer *sharedMemory;
        strcpy(message,sharedMemory->message);
    }
    return 0;
}
