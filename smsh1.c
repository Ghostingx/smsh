/*************************************************************************
    > File Name: smsh1.c
    > Author: ghost
    > Mail: zangzhaohu@gmail.com
    > Created Time: 2018年08月19日 星期日 15时47分06秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "smsh.h"

#define DFL_PROMPT ">>>"

int main()
{
    char * cmdline, * prompt, **arglist;
    int result;
    void setup();

    prompt = DFL_PROMPT;
    setup();

    while((cmdline = next_cmd(prompt,stdin)) != NULL){
        if((arglist = splitline(cmdline)) != NULL){
            result = execute(arglist);
            freelist(arglist);
        }
        free(cmdline);
    }
    return 0;
}

void setup()
    /*
     * purpose:initial the shell
     *returns:noting. calls fatal() if trouble
    */
{
    signal(SIGINT,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);
}

void fatal(char * s1, char * s2, int n)
{
    fprintf(stderr,"ERROR: %s, %s\n",s1,s2);
    exit(n);
}
