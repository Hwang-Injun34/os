#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void print_process_info(const char* name){
    printf("%s: PID=%d, PPID=%d\n", name, (int)getpid(), (int)getppid());
    fflush(stdout);
}

int main(int argc, char *argv[]){
    printf("hello world(pid: %d)\n", (int)getpid());
    fflush(stdout); // 버퍼 비우기

    pid_t pid = fork();

    if(pid < 0){
        perror("fork failed\n");
        exit(1);
    }
    else if (pid == 0) {
        print_process_info("Child");
        sleep(3);
        print_process_info("Child is done");
        exit(42);
    }
    else {
        int status;
        printf("Parent waiting for child ...\n");
        fflush(stdout);

        pid_t child_pid = wait(&status);
        
        printf("Child %d finished\n", child_pid);
        if(WIFEXITED(status)){
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        }
        print_process_info("Parent");
    }
    return 0;
}