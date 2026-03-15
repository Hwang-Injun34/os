#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    const char *filename = "test.txt";

    // 파일 열기
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd < 0){
        perror("open failed");
        exit(1);
    }

    printf("File '%s' open with FD: %d\n", filename, fd);

    // 파일 쓰기
    const char *text = "Hello, File Descriptor!\n";
    if(write(fd, text, strlen(text)) != strlen(text)) {
        perror("write failed");
        close(fd);
        exit(1);
    }

    // 파일 읽기 위해 FD 위치 이동
    lseek(fd, 0, SEEK_SET);

    char buffer[100];
    int n = read(fd, buffer, sizeof(buffer));
    if(n < 0){
        perror("read failed");
        close(fd);
        exit(1);
    }

    buffer[n] = '\0';
    printf("Read from file: %s\n", buffer);
    close(fd);
    
    return 0;
}