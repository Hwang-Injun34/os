#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
    printf("Parent(pid: %d)\n", (int)getpid());

    int pipefd[2];
    if(pipe(pipefd) == -1){perror("pipe failed"); exit(1);}

    pid_t pid1 = fork();
    if(pid1 < 0){perror("fork failed"), exit(1);}

    if(pid1 == 0){
        printf("Child1(pid:%d)\n", (int)getpid());
        
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        execlp("ls", "ls", NULL);
        perror("exec ls failed");
        exit(1);
    }

    pid_t pid2 = fork();
    if(pid2 < 0){perror("fork failed"), exit(1);}

    if(pid2 == 0){
        printf("Child2(pid:%d)\n", (int)getpid());
        
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);

        execlp("grep", "grep", "txt", NULL);
        perror("exec grep failed");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);

}