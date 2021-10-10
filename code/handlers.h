#ifndef __HANDLERS_H
#define __HANDLERS_H

extern pid_t shell_id;
extern struct Node fg_proc;

void bg_handler(int signal);
void c_handler(int signal);
void z_handler(int signal);

#endif