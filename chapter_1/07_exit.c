#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    pid_t pid = fork();

    if(pid == 0){
        printf("Child running ...\n");
        fflush(stdout);
        exit(5);
    } else{
        int status;
        wait(&status);
        if(WIFEXITED(status)) printf("Child exited with code %d\n", WEXITSTATUS(status));
    }

    return 0;
}