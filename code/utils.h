#ifndef __UTILS_H
#define __UTILS_H

extern char home_dir[];

void untildefy(char final_path[], char tilde_path[]);
void tildefy(char short_path[], char path[]);
long int hash(char *str);
int strtoi(char *str);
bool withinSixMonths(struct tm past, struct tm future);
void space_join(char dest[], int slen, char *str_list[]);

#endif