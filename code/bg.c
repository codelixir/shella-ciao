#include "headers.h"
#include "bg.h"
#include "utils.h"
#include "structs.h"

void bg(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "bg: Invalid number of arguments\n");
        return;
    }

    int job_num = strtoi(argv[1]);
    int pid = job_find(job_num);

    if (pid < 0)
    {
        fprintf(stderr, "bg: Invalid job number: %s\n", argv[1]);
        return;
    }

    if (kill(pid, SIGCONT) < 0)
    {
        perror("bg");
        return;
    }
}