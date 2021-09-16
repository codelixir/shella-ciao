#include "headers.h"
#include "execute.h"
#include "syscom.h"
#include "cd.h"
#include "pwd.h"
#include "echo.h"

void execute(char *command)
{
    char *tokenize = strtok(command, " \t\r\n");
    char *argv[32];
    int argc = 0;
    do
    {
        argv[argc++] = tokenize;
        tokenize = strtok(NULL, " \t\r\n");
    } while (tokenize != NULL);

    if (!argv[0])
    {
        return;
    }

    switch (hash(argv[0]))
    {
    case CD:
        cd(argc, argv);
        break;
    case PWD:
        pwd(argc);
        break;
    case ECHO:
        echo(argc, argv);
        break;
    case EXIT:
        running = false;
        break;
    default:
    {
        bool is_bg = false;
        if (argv[argc - 1][0] == '&')
        {
            is_bg = true;
            argv[argc - 1] = NULL;
        }
        else
        {
            argv[argc] = NULL;
        }
        syscom(argv, is_bg);
    }
    }
}

long int hash(char *str)
{
    long int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + tolower(c);

    return hash;
}