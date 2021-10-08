#include "headers.h"
#include "sig.h"
#include "utils.h"
#include "structs.h"

void sig(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "sig: Invalid number of arguments\n");
        return;
    }

    int job_num = strtoi(argv[1]);
    int sig_num = strtoi(argv[2]);
    int pid = job_find(job_num);

    if (pid < 0)
    {
        fprintf(stderr, "sig: Invalid job number: %s\n", argv[1]);
        return;
    }

    if (kill(pid, sig_num) < 0)
    {
        perror("sig");
        return;
    }
}