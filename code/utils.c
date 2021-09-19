#include "headers.h"
#include "utils.h"
#include "prompt.h"

void untildefy(char final_path[], char tilde_path[])
{
    if (tilde_path[0] != '~')
    {
        strcpy(final_path, tilde_path);
        return;
    }
    int n = strlen(tilde_path);
    for (int i = 0; i < n - 1; i++)
    {
        tilde_path[i] = tilde_path[i + 1];
    }
    tilde_path[n - 1] = '\0';
    strcpy(final_path, home_dir);
    strcat(final_path, tilde_path);
}

void tildefy(char short_path[], char path[])
{

    int path_len = strlen(path);
    int home_len = strlen(home_dir);
    short_path[0] = '~';
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
                short_path[i - home_len + 1] = path[i];
            }
            short_path[path_len - home_len + 1] = '\0';
        }
    }
    else
    {
        tilde = false;
    }

    if (!tilde)
        strcpy(short_path, path);
}

long int hash(char *str)
{
    long int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + tolower(c);

    return hash;
}

int strtoi(char *str)
{
    int x = 0;
    int n = strlen(str);

    for (int i = 0; i < n; i++)
    {
        int y = str[i] - '0';
        if (y > 9 || y < 0)
        {
            return -1;
        }
        x = x * 10 + y;
    }
    return x;
}

bool withinSixMonths(struct tm past, struct tm future)
{

    if (past.tm_year == future.tm_year)
    {
        if ((future.tm_yday - past.tm_yday) >= 183)
            return false;
        return true;
    }
    else if (past.tm_year == future.tm_year - 1)
    {
        if ((future.tm_yday + 365 - past.tm_yday) >= 183)
            return false;
        return true;
    }
    return false;
}

void bg_proc_add(int pid, char *pname)
{
    struct Node *duplicate = bg_proc_list;
    while (duplicate->next)
    {
        duplicate = duplicate->next;
    }

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->id = pid;
    strcpy(temp->name, pname);
    temp->next = NULL;

    duplicate->next = temp;
}

void bg_handler(int signal)
{
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    struct Node *previous = bg_proc_list;
    struct Node *duplicate = previous->next;

    while (previous->next)
    {
        if (duplicate->id == pid)
            break;
        previous = duplicate;
        duplicate = duplicate->next;
    }

    if (duplicate)
    {
        char status_str[12];
        WIFEXITED(status) ? strcpy(status_str, "normally") : strcpy(status_str, "abnormally");
        fprintf(stderr, "\n%s with pid %d exited %s\n", duplicate->name, duplicate->id, status_str);
        previous->next = duplicate->next;
        free(duplicate);
        prompt();
        fflush(stdout);
    }
}