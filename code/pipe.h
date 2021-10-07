#ifndef __PIPE_H
#define __PIPE_H

extern int shell_stdout;
extern int shell_stdin;

void master(int argc, char *argv[]);

#endif