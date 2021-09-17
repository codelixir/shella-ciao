#ifndef __LS_H
#define __LS_H

extern int optind;
extern char home_dir[];

void ls(int argc, char *argv[]);
void list(char *file, bool flag_l, bool flag_a, bool multiple);

#endif