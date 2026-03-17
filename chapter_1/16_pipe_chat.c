#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>



#define BUF_SIZE 100

// 단방향
int main(int argc, char *argv[]){
    printf("Parent(pid: %d)\n", (int)getpid());

    int pipefd[2];
    char buffer[BUF_SIZE];

    if(pipe(pipefd) == -1){perror("pipe failed"); exit(1);}

    pid_t pid = fork();
    if(pid < 0){perror("fork failed"); exit(1);}

    if(pid == 0){
        // printf("Child(pid: %d) - read \n", (int)getpid());

        close(pipefd[1]);

        while(1){ // 반복문 사용 이유 파악하기
            int n = read(pipefd[0], buffer, BUF_SIZE - 1);

            if(n <= 0) break; // 내용없으면 빠져나오기

            buffer[n] = '\0';
            printf("Child received: %s\n", buffer);
            fflush(stdout);
        }
        close(pipefd[0]);
    }
    else {
        // printf("Parent - write\n");

        close(pipefd[0]);

        while(1){
            printf("Parent input:");
            fflush(stdout);

            fgets(buffer, BUF_SIZE, stdin);

            //종료 조건
            if(strncmp(buffer, "exit", 4) == 0) break;

            write(pipefd[1], buffer, strlen(buffer));

        }
        close(pipefd[1]);
    }
    return 0;
}