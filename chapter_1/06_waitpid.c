#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("hello world(pid: %d)\n", (int)getpid());
    fflush(stdout); // 버퍼 비우기

    pid_t pid1 = fork();
    if(pid1 == 0) {
        printf("Child start (PID: %d)\n", getpid());
        sleep(3);
        printf("Child1 done\n");
        exit(10);
    }

    pid_t pid2 = fork();
    if(pid2 == 0){
        printf("Child2 strat (PID: %d)\n", getpid());
        sleep(1);
        printf("Child2 done\n");
        exit(20);
    }

    int status;
    pid_t wpid;

    wpid = waitpid(pid2, &status, 0);
    printf("waitpid() retuned: %d\n", wpid);
    if(WIFEXITED(status)) printf("Child2 exited with %d\n", WEXITSTATUS(status));

    wpid = wait(&status);
    printf("wait() returned: %d\n", wpid);
    if(WIFEXITED(status)) printf("Child1 exited with %d\n", WEXITSTATUS(status));

    printf("Parent done\n");
    
    return 0;
}