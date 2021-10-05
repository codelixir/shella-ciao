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