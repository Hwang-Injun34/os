#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    int fd = open("redirect.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd < 0){ perror("open failed"); exit(1); }

    dup2(fd, STDOUT_FILENO);

    printf("This goes to the file\n");
    printf("Not to the terminal\n");

    close(fd);

    return 0;
}