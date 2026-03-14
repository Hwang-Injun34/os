#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("Before fork\n");

    fork();
    printf("After fork\n");

    return 0;
}