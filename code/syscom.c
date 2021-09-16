#include "headers.h"
#include "syscom.h"

void syscom(char *argv[], bool is_bg)
{
    int forkReturn = fork();

    if (forkReturn < 0)
    {
        perror(argv[0]);
    }
    else if (forkReturn == 0)
    {
        // child process
        if (execvp(argv[0], argv) < 0)
        {
            perror(argv[0]);
        }
    }
    else
    {
        // parent process
        if (is_bg)
        {
            // if child is background process, print pid of child
            printf("%d\n", forkReturn);
        }
        else
        {
            // if child is foreground process, wait for it to finish
            wait(NULL);
        }
    }
};