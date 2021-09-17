#include "headers.h"
#include "execute.h"
#include "utils.h"
#include "syscom.h"
#include "cd.h"
#include "pwd.h"
#include "echo.h"
#include "repeat.h"
#include "ls.h"

void execute(int argc, char *argv[])
{
    if (!argv[0] || !running)
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
    case REPEAT:
        repeat(argc, argv);
        break;
    case LS:
        ls(argc, argv);
        break;
    case EXIT:
        running = false;
        printf("Bye!\n");
        return;
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