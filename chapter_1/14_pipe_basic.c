#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
    int pipefd[2];

    if(pipe(pipefd) == -1){perror("pipe failed"); exit(1);}

    pid_t pid = fork();

    if(pid < 0){
        perror("fork failed");
        exit(1);
    }
    else if(pid == 0){
        close(pipefd[1]);

        char buffer[100];
        int n = read(pipefd[0], buffer, sizeof(buffer));

        if(n < 0){perror("read failed"); exit(1);}
        buffer[n] = '\0';
        printf("Child received: %s\n", buffer);
        close(pipefd[0]);
    }
    else {
        close(pipefd[0]);

        const char *msg = "Hello world - parent";
        write(pipefd[1], msg, strlen(msg));
        close(pipefd[1]);
    }


    return 0;
}