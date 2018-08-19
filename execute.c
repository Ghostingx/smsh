/*************************************************************************
    > File Name: execute.c
    > Author: ghost
    > Mail: zangzhaohu@gmail.com
    > Created Time: 2018年08月19日 星期日 15时57分57秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int execute(char * argv[])
    /*
     * purpose: run a programe passing it arguments
     * returns: status returned via wait, or -1 on eror
     * errors: -1 on fork() or wait() errors
     *
    */
{
    int pid;
    int child_info = -1;

    if(argv[0] == NULL) //nothing succeeds
        return 0;
    if((pid = fork()) == -1)
        perror("fork()");
    else if(pid == 0){
        signal(SIGINT,SIG_DFL);
        signal(SIGQUIT,SIG_DFL);
        execvp(argv[0],argv);
        perror("cannot execute command!!!");
        exit(1);
    }
    else{
        if(wait(&child_info) ==-1)
            perror("wait()");
    }
    return child_info;
}
