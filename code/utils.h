#ifndef __UTILS_H
#define __UTILS_H

extern char home_dir[];

void untildefy(char final_path[], char tilde_path[]);
void tildefy(char short_path[], char path[]);
long int hash(char *str);
int strtoi(char *str);
bool withinSixMonths(struct tm past, struct tm future);
void bg_proc_add(int pid, char *pname);
void bg_handler(int signal);

struct Node
{
    int id;
    struct Node *next;
    char name[30];
};

extern struct Node *bg_proc_list;

#endif