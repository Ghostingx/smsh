/*************************************************************************
    > File Name: smsh.h
    > Author: ghost
    > Mail: zangzhaohu@gmail.com
    > Created Time: 2018年08月19日 星期日 16时53分03秒
 ************************************************************************/
#include <stdio.h>

#define YES 1
#define NO  0

char * next_cmd();
char **splitline(char*);
void freelist(char **);
void *emalloc(size_t);
void * erealloc(void *,size_t);
int execute(char **);
void fatal(char *,char *,int);


