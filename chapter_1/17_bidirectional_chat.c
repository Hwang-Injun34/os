#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUF_SIZE 100 

int main(int argc, char *argv[]){
    int pipe1[2];
    int pipe2[2];

    char buffer[BUF_SIZE];

    if(pipe(pipe1) == -1 || pipe(pipe2) == -1) {perror("child failed"); exit(1);}

    pid_t pid = fork();
    if(pid < 0){perror("fork failed"); exit(1);}

    if(pid == 0){
        close(pipe1[1]); // pipe1[1]: write 닫기 
        close(pipe2[0]); // pipe2[0]: read 닫기 

        while(1){
            // 부모 메시지 받기
            int n = read(pipe1[0], buffer, BUF_SIZE -1);
            if(n<=0) break;

            buffer[n] = '\0';
            printf("\n[Child received]: %s", buffer);
            fflush(stdout);

            // 종료 조건
            if(strncmp(buffer, "exit", 4) == 0) break;

            // 응답 보내기
            printf("[Child input]: ");
            fflush(stdout);

            fgets(buffer, BUF_SIZE, stdin);
            write(pipe2[1], buffer, strlen(buffer));

            if(strncmp(buffer, "exit", 4) == 0) break;
        }
        close(pipe1[0]);
        close(pipe2[1]);
    }

    else{
        close(pipe1[0]); // read 닫기
        close(pipe2[1]); // write 닫기
        
        while(1){
            printf("[Parent input]: ");
            fflush(stdout);

            fgets(buffer, BUF_SIZE, stdin);

            write(pipe1[1], buffer, strlen(buffer));

            if(strncmp(buffer, "exit", 4) == 0) break;

            // 자식 응답 듣기
            int n = read(pipe2[0], buffer, BUF_SIZE-1);
            if(n <= 0) break;

            buffer[n] = '\0';
            printf("[Parent recived]: %s", buffer);
        }
        close(pipe1[1]);
        close(pipe2[0]);
    }
    
    return 0;
}