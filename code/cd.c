#include "headers.h"
#include "cd.h"
#include "utils.h"

void cd(int argc, char *argv[])
{

    char dir[1024];
    char path[2048];
    char cwd[1024];
    getcwd(cwd, 1024);

    if (argc > 2)
    {
        fprintf(stderr, "cd: Too many arguments\n");
        return;
    }
    else if (argc == 1)
    {
        strcpy(dir, "~");
    }
    else
    {
        strcpy(dir, argv[1]);
    }

    switch (dir[0])
    {
    case '-':
        if (strlen(dir) > 1)
        {
            fprintf(stderr, "cd: No such file or directory: %s\n", dir);
            return;
        }
        strcpy(path, prev_dir);
        printf("%s\n", prev_dir);
        break;
    case '~':
    {
        untildefy(path, dir);
        break;
    }
    case '.':
        sprintf(path, "%s/%s", cwd, dir);
        break;
    default:
        strcpy(path, dir);
    }

    if (chdir(path) < 0)
    {
        perror("cd");
        return;
    }

    strcpy(prev_dir, cwd);
}