#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_process_info(const char* name){
    printf("%s: PID=%d, PPID=%d\n", name, (int)getpid(), (int)getppid());
    fflush(stdout);
}

int main(int argc, char *argv[])
{
    printf("hello world(pid: %d)\n", (int)getpid());
    fflush(stdout);
    
    pid_t pid1 = fork();
    if(pid1 < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    pid_t pid2 = fork();
    if(pid2 < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } 
    
    // 프로세스 구분
    if(pid1 == 0 && pid2 == 0){
        print_process_info("Child3");
    } else if(pid1 == 0 ){
        print_process_info("Child1");
    } else if(pid2 == 0) {
        print_process_info("Child2");
    } else{
        print_process_info("Parent");
    }
    return 0;
}