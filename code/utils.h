#ifndef __UTILS_H
#define __UTILS_H

extern char home_dir[];

void untildefy(char final_path[], char tilde_path[]);
long int hash(char *str);
int strtoi(char *str);
bool withinSixMonths(struct tm past, struct tm future);

#endif