#include "headers.h"
#include "fg.h"
#include "utils.h"
#include "structs.h"

void fg(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "fg: Invalid number of arguments\n");
        return;
    }

    int job_num = strtoi(argv[1]);
    int pid = job_find(job_num);

    if (pid < 0)
    {
        fprintf(stderr, "fg: Invalid job number: %s\n", argv[1]);
        return;
    }

    //ignore signal
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);

    tcsetpgrp(STDIN_FILENO, pid);
    waitpid(pid, NULL, 0);
    tcsetpgrp(STDIN_FILENO, pid);

    // default signal handling
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
}