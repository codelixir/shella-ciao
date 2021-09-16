#include "headers.h"
#include "execute.h"
#include "cd.h"
#include "pwd.h"

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

    switch (hash(argv[0]))
    {
    case CD:
        cd(argc, argv);
        break;
    case PWD:
        pwd(argc);
        break;
    case EXIT:
        running = false;
        break;
    default:
        printf("Invalid command\n");
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