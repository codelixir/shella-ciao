#include "headers.h"
#include "syscom.h"
#include "handlers.h"
#include "structs.h"

void syscom(char *argv[], bool is_bg)
{
    int fork_ret = fork();

    if (fork_ret < 0)
    {
        perror(argv[0]);
    }
    else if (fork_ret == 0)
    {
        // child process
        setpgid(fork_ret, fork_ret);
        if (execvp(argv[0], argv) < 0)
        {
            perror(argv[0]);
        }
    }
    else
    {
        // parent process
        int child_id = fork_ret;
        setpgid(child_id, child_id);

        /* return terminal control to shell in case
        it had been given to another process */
        dup2(shell_stdin, STDIN_FILENO);
        dup2(shell_stdout, STDOUT_FILENO);

        if (is_bg)
        {
            bg_proc_add(child_id, argv[0]);
            // if child is background process, print pid of child
            printf("%d\n", child_id);
            signal(SIGCHLD, bg_handler);
        }
        else
        {
            //ignore signal
            signal(SIGTTOU, SIG_IGN);
            signal(SIGTTIN, SIG_IGN);

            tcsetpgrp(STDIN_FILENO, child_id);
            // if child is foreground process, wait for it
            waitpid(child_id, NULL, 0);
            tcsetpgrp(STDIN_FILENO, shell_id);

            // default signal handling
            signal(SIGTTOU, SIG_DFL);
            signal(SIGTTIN, SIG_DFL);

            return;
        }
    }
}
