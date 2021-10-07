#include "headers.h"
#include "structs.h"
#include "utils.h"

void bg_proc_add(int pid, int argc, char *argv[])
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

    // test
    printf("[%d] Adding job %s with id %d\n", job_count, temp->name, pid);

    duplicate->next = temp;
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