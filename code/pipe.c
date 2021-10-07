#include "headers.h"
#include "pipe.h"
#include "execute.h"

void master(int argc, char *argv[])
{
    int pipe_index = -1;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "|") == 0)
        {
            pipe_index = i;
            break;
        }
    }

    fprintf(stderr, "[%d] %d\n", getpid(), pipe_index); // test

    if (pipe_index == -1)
    {
        // no piping
        execute(argc, argv);
    }
    else
    {
        // piping

        // create a pipe
        int tube[2];
        if (pipe(tube) < 0)
        {
            perror("|");
            return;
        }

        // LEFT HAND SIDE | ...

        // write to pipe
        if (dup2(tube[1], STDOUT_FILENO) < 0)
        {
            perror("|");
            return;
        }

        // execute command
        execute(pipe_index, argv);

        dup2(shell_stdout, STDOUT_FILENO);
        close(tube[1]);

        // ... | RIGHT HAND SIDE

        // read from pipe
        if (dup2(tube[0], STDIN_FILENO) < 0)
        {
            perror("|");
            return;
        }

        // remaining arguments
        char *new_argv[32];
        for (int k = 0; k < 32; k++)
            new_argv[k] = (char *)malloc(sizeof(char) * 1000);
        for (int j = pipe_index + 1; j < argc; j++)
        {
            strcpy(new_argv[j - pipe_index - 1], argv[j]);
        }

        // recursively execute the remaining commands
        master(argc - pipe_index - 1, new_argv);

        close(tube[0]);
    }

    /* return stdin/stdout to shell terminal in
    case it had been assigned to another fd */

    dup2(shell_stdin, STDIN_FILENO);
    dup2(shell_stdout, STDOUT_FILENO);
}