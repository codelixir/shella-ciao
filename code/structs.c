#include "headers.h"
#include "structs.h"

void bg_proc_add(int pid, char *pname)
{
    struct Node *duplicate = bg_proc_list;
    while (duplicate->next)
    {
        duplicate = duplicate->next;
    }

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->id = pid;
    strcpy(temp->name, pname);
    temp->next = NULL;

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