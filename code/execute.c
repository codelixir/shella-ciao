#include "headers.h"
#include "execute.h"
#include "structs.h"
#include "utils.h"
#include "syscom.h"
#include "cd.h"
#include "pwd.h"
#include "echo.h"
#include "repeat.h"
#include "ls.h"
#include "pinfo.h"
#include "redirection.h"
#include "jobs.h"
#include "sig.h"

void execute(int argc, char *argv[])
{
    if (!argc || !argv[0] || !running || check_redirection(&argc, argv))
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
    case PINFO:
        pinfo(argc, argv);
        break;
    case JOBS:
        jobs(argc, argv);
        break;
    case SIG:
        sig(argc, argv);
        break;
    case EXIT:
        running = false;
        return;
    default:
    {
        bool is_bg = false;
        if (argv[argc - 1][0] == '&')
        {
            is_bg = true;
            argv[--argc] = NULL;
        }
        else
        {
            argv[argc] = NULL;
        }
        syscom(argc, argv, is_bg);
    }
    }
    close_all_files();
}