#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
    int fd = open("fork_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(fd < 0){
        perror("open failed");
        exit(1);
    }

    pid_t pid = fork();

    if(pid < 0){
        perror("fork failed");
        exit(1);
    }
    else if(pid == 0){
        const char *child_msg = "Child writing\n";
        if(write(fd, child_msg, strlen(child_msg)) != strlen(child_msg)){
            perror("write failed");
            close(fd);
            exit(1);
        }
        printf("%s", child_msg);
    }
    else {
        const char *parent_msg = "Parrent writing\n";
        if(write(fd, parent_msg, strlen(parent_msg)) != strlen(parent_msg)){
            perror("write failed");
            close(fd);
            exit(1);
        }
        printf("%s", parent_msg);
        wait(NULL);
    }

    close(fd);

    return 0;
}