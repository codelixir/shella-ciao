#include "headers.h"
#include "structs.h"
#include "utils.h"
#include "prompt.h"

void job_add(int pid, int argc, char *argv[])
{
    struct Node *duplicate = bg_proc_list;
    while (duplicate->next)
    {
        duplicate = duplicate->next;
    }

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->id = pid;
    temp->j_num = ++job_count;
    space_join(temp->name, argc, argv);
    temp->next = NULL;

    duplicate->next = temp;
}

int job_find(int job_num)
{

    int pid = -1;
    struct Node *duplicate = bg_proc_list->next;

    while (duplicate)
    {
        if (duplicate->j_num == job_num)
        {
            pid = duplicate->id;
            break;
        }
        duplicate = duplicate->next;
    }

    return pid;
}

int job_remove(int job_num)
{
    struct Node *previous = bg_proc_list;
    struct Node *duplicate = previous->next;

    while (previous->next)
    {
        if (duplicate->j_num == job_num)
            break;
        previous = duplicate;
        duplicate = duplicate->next;
    }

    if (duplicate)
    {
        previous->next = duplicate->next;
        free(duplicate);
    }
}

void track_file(int fd)
{
    open_files.list[open_files.count++] = fd;
}

void close_all_files()
{
    while (open_files.count > 0)
    {
        close(open_files.list[(open_files.count--) - 1]);
    }
}