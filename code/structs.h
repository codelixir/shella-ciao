#ifndef __STRUCTS_H
#define __STRUCTS_H

struct Node
{
    int id;
    int j_num;
    struct Node *next;
    char name[256];
};

extern int job_count;
extern struct Node *bg_proc_list;
void bg_proc_add(int pid, int argc, char *argv[]);

struct Vector
{
    int count;
    int list[32];
};

extern struct Vector open_files;
void track_file(int fd);
void close_all_files();

#endif