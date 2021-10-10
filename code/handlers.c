#include "headers.h"
#include "handlers.h"
#include "structs.h"
#include "prompt.h"

void bg_handler(int signal)
{
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    struct Node *previous = bg_proc_list;
    struct Node *duplicate = previous->next;

    while (previous->next)
    {
        if (duplicate->id == pid)
            break;
        previous = duplicate;
        duplicate = duplicate->next;
    }

    if (duplicate)
    {
        char status_str[12];
        WIFEXITED(status) ? strcpy(status_str, "normally") : strcpy(status_str, "abnormally");
        fprintf(stderr, "\n%s with pid %d exited %s\n", duplicate->name, duplicate->id, status_str);
        previous->next = duplicate->next;
        free(duplicate);
        prompt();
        fflush(stdout);
    }
}

void c_handler(int signal)
{
    int pid = getpid();

    if (pid < 0)
    {
        perror("Error");
    }
    // child process
    else if (pid != shell_id)
    {
        return;
    }
    // parent process
    else
    {
        if (fg_proc.id < 0)
        {
            printf("\n");
            prompt();
            fflush(stdout);
            return;
        }
        else
        {
            kill(fg_proc.id, SIGINT);
            fg_proc.id = -1;
            fflush(stdout);
        }
    }
}

void z_handler(int signal)
{
    int pid = getpid();

    if (pid < 0)
    {
        perror("Error");
    }
    // child process
    else if (pid != shell_id)
    {
        return;
    }
    // parent process
    else
    {
        if (fg_proc.id < 0)
        {
            printf("\n");
            prompt();
            fflush(stdout);
            return;
        }
        else
        {
            kill(fg_proc.id, SIGTTIN);
            kill(fg_proc.id, SIGTSTP);
            fprintf(stderr, "%d\n", fg_proc.id);

            proc_job();
            prompt();
            fflush(stdout);
        }
    }
}