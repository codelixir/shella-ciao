#include "headers.h"
#include "repeat.h"
#include "utils.h"
#include "execute.h"

void repeat(int argc, char *argv[])
{

    int freq = strtoi(argv[1]);

    if (freq < 0)
    {
        fprintf(stderr, "repeat: Invalid frequency: %s\n", argv[1]);
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
