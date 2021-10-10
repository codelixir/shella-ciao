#include "headers.h"
#include "utils.h"

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

void space_join(char dest[], int slen, char *str_list[])
{
    if (!slen)
    {
        strcpy(dest, " ");
        return;
    }

    strcpy(dest, str_list[0]);
    for (int i = 1; i < slen; i++)
    {
        strcat(dest, " ");
        strcat(dest, str_list[i]);
    }
}