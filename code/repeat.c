#include "headers.h"
#include "repeat.h"
#include "execute.h"

void repeat(int argc, char *argv[])
{

    int freq = strtoi(argv[1]);

    if (freq < 0)
    {
        printf("repeat: Invalid frequency: %s\n", argv[1]);
    }

    char *newargs[32];

    for (int i = 0; i < argc - 2; i++)
    {
        newargs[i] = argv[i + 2];
    }

    for (int i = 1; i <= freq; i++)
    {
        execute(argc - 2, newargs);
    }
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