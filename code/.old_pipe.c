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
        // no piping (end condition)
        execute(argc, argv);
    }
    else
    {
        // piping (recursively call master function)

        // create a pipe
        int tube[2];
        if (pipe(tube) < 0)
        {
            perror("|");
            return;
        }

        // create a fork
        int fork_ret = fork();
        if (fork_ret < 0)
        {
            perror("|");
            return;
        }
        else if (fork_ret == 0)
        {
            // child process
            close(tube[1]);

            // read from pipe
            if (dup2(tube[0], STDIN_FILENO) < 0)
            {
                perror("|");
                return;
            }

            // remaining arguments
            char *new_argv[32];
            for (int j = pipe_index + 1; j < argc; j++)
            {
                strcpy(new_argv[j - pipe_index - 1], argv[j]);
            }

            // recursively execute the remaining commands
            master(argc - pipe_index - 1, new_argv);

            close(tube[0]);
            exit(0);
        }
        else
        {
            // parent process
            close(tube[0]);

            // write to pipe
            if (dup2(tube[1], STDOUT_FILENO) < 0)
            {
                perror("|");
                return;
            }

            // execute command
            execute(pipe_index, argv);

            close(tube[1]);
        }
    }

    /* return stdin/stdout to shell terminal in
    case it had been assigned to another fd */

    dup2(shell_stdin, STDIN_FILENO);
    dup2(shell_stdout, STDOUT_FILENO);
}