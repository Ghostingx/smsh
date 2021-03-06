/*************************************************************************
    > File Name: splitline.c
    > Author: ghost
    > Mail: zangzhaohu@gmail.com
    > Created Time: 2018年08月19日 星期日 16时07分38秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "smsh.h"

char * next_cmd(char * prompt, FILE * fp)
    /*
     * purpose: read next command line from fp
     * returns: dynamically allocated string holding command line
     * errors:  NULL at EOF (not really an error)
     *          calls fatal from emalloc()
     * notes: allocates space in BUFSIZ chunks
    */
{
    char * buf;                     // the buffer
    int bufspace = 0;               //total size
    int pos = 0;                    //current position
    int c;                          //input char

    printf("%s",prompt);
    while((c = getc(fp)) != EOF){
        // need spaces?
        if(pos+1 >= bufspace){     // 1 for \0
            if(bufspace == 0)       // y:1st time
                buf = emalloc(BUFSIZ);
            else                    //or expand
                buf = erealloc(buf,bufspace + BUFSIZ);
            bufspace += BUFSIZ;
        }
        if (c == '\n')              // end of command?
            break;
        buf[pos++] = c;             // no add to buffer
    }
    if ( c== EOF && pos == 0)       //EOF and no input
        return NULL;
    buf[pos] = '\0';
    return buf;
}
/*
 * splitline( parse a line into an array os strings )
*/
#define is_delim(x) ((x) == ' ' || (x) == '\t')
char ** splitline(char * line)
    /*
     * purpose: split a line into an array of white-space separated tokens
     * returns: a NULL-terminated array of pointers to cppies of the
     *          tokens or NULL if lineif no tokens on the line
     * action: traverse the array ,locate strings,make copies
     * note: strtok() could work,but we may want to add quotes later
    */

{
    char * newstr();
    char **args;
    int spots = 0;                  // spots in table
    int bufspace = 0;               // bytes in tables
    int argnum = 0;                 // slot used
    char *cp = line;                // pos in string
    char * start;
    int len;

    if (NULL == line)
        return NULL;

    args = emalloc(BUFSIZ);         //initialize array
    bufspace = BUFSIZ;
    spots = BUFSIZ/sizeof(char *);

    while( *cp != '\0')
    {
        while(is_delim(*cp))
            cp++;
        if(*cp == "\0")
            break;

        //make sure the array has room ( +1 for NULL)
        if(argnum + 1 >= spots){
            args = erealloc(args,bufspace + BUFSIZ);
            bufspace += BUFSIZ;
            spots += (BUFSIZ/sizeof(char *));
        }
        // mark start ,then find end of word
        start = cp;
        len = 1;
        while(*++cp != '\0' && (is_delim(*cp)))
            len++;
        args[argnum++] = newstr(start,len);
    }
    args[argnum] = NULL;
    return args;
}

char *newstr(char *s ,int l)
    /* purpose: constructor for strings
     * returns: a string , never NULL
    */
{
    char * rv = emalloc(l+1);
    rv[l] = '\0';
    strncpy(rv,s,l);
    return rv;
}

void freelist(char ** list)
    /* purpose: free the list returned by splitline
     * returns: nothing
     * action: free all strings in list and then free the list
    */
{
    char ** cp = list;
    while(*cp)
        free(*cp++);
    free(list);
}
void * emalloc(size_t n){
    void *rv;
    if((rv = malloc(n)) == NULL)
        fatal("out of memory","",1);
    return rv;
}
void * erealloc(void * p, size_t n){
    void *rv;
    if((rv = realloc(p,n)) == NULL)
        fatal("realloc() failed","",1);
    return rv;
}
