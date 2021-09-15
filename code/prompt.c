#include "prompt.h"
#include "headers.h"

void prompt()
{
    char system_name[256];
    char path[1024];
    char curr_dir[1024] = "~";

    uid_t uid = geteuid();
    struct passwd *system_uid = getpwuid(uid);
    char *username = system_uid->pw_name;

    gethostname(system_name, 256);
    getcwd(path, 1024);

    int path_len = strlen(path);
    int home_len = strlen(home_dir);
    bool tilde = true;

    if (path_len >= home_len)
    {
        for (int i = 0; i < home_len; i++)
        {
            if (path[i] != home_dir[i])
                tilde = false;
        }
        if (tilde)
        {
            for (int i = home_len; i < path_len; i++)
            {
                curr_dir[i - home_len + 1] = path[i];
            }
        }
    }
    else
    {
        tilde = false;
    }

    if (tilde)
        printf("<%s@%s:%s> ", username, system_name, curr_dir);
    else
        printf("<%s@%s:%s> ", username, system_name, path);
}
