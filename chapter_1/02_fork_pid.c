#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    
    printf("hello world(pid: %d)\n", (int)getpid());

    pid_t pid = fork();

    if(pid < 0){ // fork 실패
            fprintf(stderr, "fork failed\n");
            exit(1);
    } else if(pid == 0){
        printf("--Child Process--\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    } else{
        printf("--Parent Process--\n");
        printf("Parent Pid: %d\n", getpid());
        printf("Child PID: %d\n", pid);
    }

    return 0;
}