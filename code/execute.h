#ifndef __EXECUTE_H
#define __EXECUTE_H

#define EXIT 6385204799
#define CD 5863276
#define PWD 193502992
#define ECHO 6385181892
#define REPEAT 6953974492262
#define LS 5863588
#define PINFO 210724269537
#define HISTORY 229468404218647

void execute(int argc, char *argv[]);

extern bool running;
extern int shell_stdout;
extern int shell_stdin;

#endif