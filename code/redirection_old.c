#include "headers.h"
#include "redirection.h"
#include "structs.h"

int check_redirection(int *argc_ptr, char *argv[])
{
    if (!argv[0] || !running)
    {
        return 0;
    }

    int argc = *argc_ptr;
    struct Vector skipped = {.count = 0};

    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '<' || argv[i][0] == '>')
        {
            // test
            fprintf(stderr, "Entered redirection case for argument %d.\n", i);

            // output redirection
            if (strcmp(argv[i], ">") == 0)
            {
                if (i == argc - 1)
                {
                    fprintf(stderr, "%s: parse error near `\\n`\n", argv[0]);
                    return 1;
                }

                // TODO: Handle special characters in file names

                fprintf(stderr, "[opening] %s\n", argv[i + 1]); // test

                // file to replace stdout
                int out_fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (out_fd < 0)
                {
                    perror(argv[i + 1]);
                    return 1;
                }

                track_file(out_fd);

                if (dup2(out_fd, STDOUT_FILENO) < 0)
                {
                    perror(argv[i + 1]);
                    return 1;
                }

                // remove `> arg` from argv
                skipped.list[skipped.count++] = i;
                skipped.list[skipped.count++] = ++i;
            }
            else if (strcmp(argv[i], ">>") == 0)
            {
                if (i == argc - 1)
                {
                    fprintf(stderr, "%s: parse error near `\\n`\n", argv[0]);
                    return 1;
                }

                fprintf(stderr, "[opening] %s\n", argv[i + 1]); // test

                // file to replace stdout
                int out_fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (out_fd < 0)
                {
                    perror(argv[i + 1]);
                    return 1;
                }

                track_file(out_fd);

                if (dup2(out_fd, STDOUT_FILENO) < 0)
                {
                    perror(argv[i + 1]);
                    return 1;
                }

                // remove `>> arg` from argv
                skipped.list[skipped.count++] = i;
                skipped.list[skipped.count++] = ++i;
            }
            // input redirection
            else if (strcmp(argv[i], "<") == 0)
            {
                if (i == argc - 1)
                {
                    fprintf(stderr, "%s: parse error near `\\n`\n", argv[0]);
                    return 1;
                }

                fprintf(stderr, "[opening] %s\n", argv[i + 1]); // test

                // file to replace stdin
                int in_fd = open(argv[i + 1], O_RDONLY, 0);
                if (in_fd < 0)
                {
                    perror(argv[i + 1]);
                    return 1;
                }

                track_file(in_fd);

                if (dup2(in_fd, STDIN_FILENO) < 0)
                {
                    perror(argv[i + 1]);
                    return 1;
                }

                // remove `< arg` from argv
                skipped.list[skipped.count++] = i;
                skipped.list[skipped.count++] = ++i;
            }
            else
            {
                fprintf(stderr, "%s: Invalid symbol or argument: %s\n", argv[0], argv[i]);
                return 1;
            }

            // test
            int skip_j = 0;
            fprintf(stderr, "Simplified command: ");
            for (int j = 0; j < argc; j++)
            {
                if (j == skipped.list[skip_j])
                {
                    if (skip_j < skipped.count)
                        skip_j++;
                    continue;
                }
                fprintf(stderr, "%s ", argv[j]);
            }
            fprintf(stderr, "\n");
        }
    }

    if (skipped.count)
    {
        int new_argc = 0, skip_ii = 0;
        char *new_argv[32];
        for (int k = 0; k < 32; k++)
            new_argv[k] = (char *)malloc(sizeof(char) * 1000);

        for (int i = 0; i < argc; i++)
        {
            if (i == skipped.list[skip_ii])
            {
                if (skip_ii < skipped.count)
                    skip_ii++;
                continue;
            }
            strcpy(new_argv[new_argc++], argv[i]);
        }

        argv = new_argv;
        *argc_ptr = new_argc;
    }
    return 0;
}