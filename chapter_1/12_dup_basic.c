#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argv, char *argc[]){
    int fd = open("dup_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd < 0){ perror("open failed"); exit(1);}

    int new_fd = dup(fd);
    printf("Origin FD: %d\n", fd);
    printf("New FD: %d\n", new_fd);
    
    const char *origin_msg = "Hello\n";
    const char *new_msg = "World\n";

    if(write(fd, origin_msg, strlen(origin_msg)) != strlen(origin_msg)){
        perror("write failed\n");
        close(fd);
        exit(1);
    }

    if(write(new_fd, new_msg, strlen(new_msg)) != strlen(new_msg)){
        perror("write failed\n");
        close(new_fd);
        exit(1);
    }

    printf("%s%s", origin_msg, new_msg);
    close(fd);
    close(new_fd);
    return 0;
}
