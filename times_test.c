#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

int main()
{
    clock_t start ,end ;
    struct tms stat ,end1;
    start = times(&stat);
    if(start ==-1){
        perror("times err");
        exit(-1);
    }
    system("sleep 2");
    end = times(&end1);
    printf("%ld\n",start);
    printf("%ld\n",end);
    exit(0);
}