#include "pwd.h"
#include "headers.h"

void pwd(int argc)
{
    if (argc > 1)
    {
        fprintf(stderr, "pwd: Too many arguments\n");
        return;
    }
    char cwd[1024];
    getcwd(cwd, 1024);
    printf("%s\n", cwd);
}