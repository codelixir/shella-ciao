#ifndef __SYSCOM_H
#define __SYSCOM_H

void syscom(int argc, char *argv[], bool is_bg);

extern pid_t shell_id;
extern int shell_stdout;
extern int shell_stdin;

#endif