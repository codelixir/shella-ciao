#ifndef __STRUCTS_H
#define __STRUCTS_H

struct Node
{
    int id;
    struct Node *next;
    char name[30];
};

extern struct Node *bg_proc_list;
void bg_proc_add(int pid, char *pname);

#endif