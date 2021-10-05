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
