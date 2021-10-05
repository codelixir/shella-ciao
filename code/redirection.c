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

    // int in_fd = open(in_file, O_RDONLY | O_APPEND, 0);
    // int out_fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '<' || argv[i][0] == '>')
        {
            // test
            printf("Entered redirection case for argument %d.\n", i);

            // output redirection
            if (strcmp(argv[i], ">") == 0)
            {
                if (i == argc - 1)
                {
                    printf("%s: parse error near `\\n`\n", argv[0]);
                    return 1;
                }

                // TODO: Handle special characters in file names

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

                // remove `>> arg` from argv
                for (int j = i + 2; j < argc; j++)
                {
                    strcpy(argv[j - 2], argv[j]);
                }
                argc -= 2;
                argv[argc] = "\0";
            }
            else if (strcmp(argv[i], ">>") == 0)
            {
                if (i == argc - 1)
                {
                    printf("%s: parse error near `\\n`\n", argv[0]);
                    return 1;
                }
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

                // remove `> arg` from argv
                for (int j = i + 2; j < argc; j++)
                {
                    strcpy(argv[j - 2], argv[j]);
                }
                argc -= 2;
                argv[argc] = "\0";
            }
            // input redirection
            else if (strcmp(argv[i], "<") == 0)
            {
                if (i == argc - 1)
                {
                    printf("%s: parse error near `\\n`\n", argv[0]);
                    return 1;
                }
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
                for (int j = i + 2; j < argc; j++)
                {
                    strcpy(argv[j - 2], argv[j]);
                }
                argc -= 2;
                argv[argc] = "\0";
            }
            else
            {
                printf("%s: Invalid symbol or argument: %s\n", argv[0], argv[i]);
                return 1;
            }
        }
    }

    *argc_ptr = argc;
    return 0;
}