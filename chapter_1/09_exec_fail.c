#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

        execl("/bin/nonexistent", "nonexistent", NULL);
        perror("execl failed");
        exit(1);
    }
    else{
        int status;
        pid_t child_pid = wait(&status);
        
        printf("Parent PID: %d, Child %d finished\n", getpid(), child_pid);
        
        if(WIFEXITED(status)) printf("Child exited with status %d\n", WEXITSTATUS(status));
        else printf("Child did not exit normally\n");
    }
    return 0;
}