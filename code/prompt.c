#include "headers.h"
#include "prompt.h"
#include "utils.h"

void prompt()
{
    char system_name[256];
    char path[1024];
    char curr_dir[1024];

    uid_t uid = geteuid();
    struct passwd *system_uid = getpwuid(uid);
    char *username = system_uid->pw_name;

    gethostname(system_name, 256);
    getcwd(path, 1024);

    tildefy(curr_dir, path);

    printf("<%s@%s:%s> ", username, system_name, curr_dir);
}
