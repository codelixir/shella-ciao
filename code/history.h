#ifndef __HISTORY_H
#define __HISTORY_H

extern char home_dir[];
extern int log_count;
extern char logs[][21];

void history(int argc, char *argv[]);
void update_logs(char *command);
void read_logs();
void write_logs();

#endif