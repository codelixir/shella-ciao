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