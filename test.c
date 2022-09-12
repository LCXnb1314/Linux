#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int ret;
    ret = sysconf(_SC_CLK_TCK);
    clock_t start ,end;
    struct tms star ,end1;
    pid_t pid ;

    start = times(&star);
    if(-1 ==start)
    {
        perror("times err");
        exit(-1);
    }
    pid = fork();
    if(fork <0)
    {
        perror("fork err");
        exit(-1);
    }
    else
        if(pid == 0)
        {

            printf("my %d   parent %d\n",getpid(),getppid());
            //sleep(2);
            _exit(0);
        }
    if(waitpid(pid,NULL,0)== -1){
        perror("waitpid err");
        exit(-1);
    }
    sleep(2);
    end = times(&end1);
    // ret = (end - start)/100;
    printf("%ld\n",star.tms_stime);
    printf("%ld\n",end1.tms_stime);
    // ret = 
    exit(0);
}
