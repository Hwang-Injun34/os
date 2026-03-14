#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    printf("Hello world(PID: %d)\n", (int)getpid());

    pid_t pid = fork();

    if(pid < 0){
        perror("fork failed\n");
        exit(1);
    }
    else if(pid == 0){
        printf("Child PID: %d before exec\n", (int)getpid());
        fflush(stdout);

        execl("/bin/ls", "ls", NULL);
        perror("execl failed");

        exit(1);
    }
    else{
        int status;
        wait(&status);
        printf("Parent PID: %d done, Child exited\n", (int)getpid());
    }

    return 0;
}