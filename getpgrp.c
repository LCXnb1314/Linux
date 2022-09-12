#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = getpgrp();
    printf("getpid %d   getpgrp %d\n",getpid(),pid);
    exit(0);
}