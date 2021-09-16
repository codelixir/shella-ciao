#include "headers.h"
#include "cd.h"

void cd(int argc, char *argv[])
{

    char dir[1024];
    char path[1024];
    char pwd[1024];
    getcwd(pwd, 1024);

    if (argc > 2)
    {
        printf("cd: Too many arguments\n");
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
            printf("cd: %s: Invalid argument\n", dir);
            return;
        }
        strcpy(path, prev_dir);
        printf("%s\n", prev_dir);
        break;
    case '~':
    {
        int n = strlen(dir);
        for (int i = 0; i < n - 1; i++)
        {
            dir[i] = dir[i + 1];
        }
        dir[n - 1] = '\0';
        strcpy(path, home_dir);
        strcat(path, dir);
        break;
    }
    case '.':
        if (!strcmp(".", dir))
        {
            strcpy(path, pwd);
        }
        else if (!strcmp("..", dir))
        {
            sprintf(path, "%s/..", pwd);
        }
        else
        {
            printf("cd: %s: Invalid argument\n", dir);
            return;
        }
        break;
    default:
        strcpy(path, dir);
    }

    if (chdir(path) < 0)
    {
        perror("cd");
        return;
    }

    strcpy(prev_dir, pwd);
}