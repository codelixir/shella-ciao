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

    for (int i = argc - 1; i >= 0; i--)
    {
        if (argv[i][0] == '<' || argv[i][0] == '>')
        {
            // test
            // printf("Entered redirection case for argument %d.\n", i);

            // output redirection
            if (strcmp(argv[i], ">") == 0)
            {
                if (i == argc - 1)
                {
                    fprintf(stderr, "%s: parse error near `\\n`\n", argv[0]);
                    return 1;
                }

                // TODO: Handle special characters in file names

                // file to replace stdout
                fprintf(stderr, "[opening] %s\n", argv[i + 1]);
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
                skipped.list[skipped.count++] = i + 1;
            }
            else if (strcmp(argv[i], ">>") == 0)
            {
                if (i == argc - 1)
                {
                    fprintf(stderr, "%s: parse error near `\\n`\n", argv[0]);
                    return 1;
                }
                // file to replace stdout
                fprintf(stderr, "[opening] %s\n", argv[i + 1]);
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
                skipped.list[skipped.count++] = i + 1;
            }
            // input redirection
            else if (strcmp(argv[i], "<") == 0)
            {
                if (i == argc - 1)
                {
                    fprintf(stderr, "%s: parse error near `\\n`\n", argv[0]);
                    return 1;
                }
                // file to replace stdin
                fprintf(stderr, "[opening] %s\n", argv[i + 1]);
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
                skipped.list[skipped.count++] = i + 1;
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
                int flag = 0;
                for (int k = 0; k < skipped.count; k++)
                {
                    if (skipped.list[k] == j)
                    {
                        flag = 1;
                    }
                }
                if (flag == 0)
                    fprintf(stderr, "%s ", argv[j]);
            }
            fprintf(stderr, "\n");
        }
    }

    int new_argc = 0, skip_ii = 0;
    char *new_argv[32];
    for (int k = 0; k < 32; k++)
    {
        new_argv[k] = (char *)malloc(sizeof(char) * 1000);
    }

    for (int j = 0; j < argc; j++)
    {
        int flag = 0;
        for (int k = 0; k < skipped.count; k++)
        {
            if (skipped.list[k] == j)
            {
                flag = 1;
            }
        }
        if (flag == 0)
            strcpy(new_argv[new_argc++], argv[j]);
    }

    argv = new_argv;
    *argc_ptr = new_argc;
    // fprintf(stderr, "**%d**\n", new_argc);
    return 0;
}