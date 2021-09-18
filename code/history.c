#include "headers.h"
#include "history.h"
#include "utils.h"

void history(int argc, char *argv[])
{
    int count;

    if (argc > 2)
    {
        printf("history: Too many arguments\n");
        return;
    }
    else if (argc == 2)
    {
        count = strtoi(argv[1]);
        if (count < 0)
        {
            printf("history: Invalid argument: %s\n", argv[1]);
        }
    }
    else if (argc == 1)
    {
        count = 20;
    }

    if (count > log_count)
    {
        count = log_count;
    }

    for (int i = log_count - 1; i >= 0; i--)
    {
        printf("%2d %s\n", log_count - i, logs[i]);
    }
}

void update_logs(char *command)
{
    for (int i = log_count; i > 0; i--)
    {
        strcpy(logs[i], logs[i - 1]);
    }
    if (log_count < 20)
        log_count++;
    command[strcspn(command, "\n")] = '\0';
    strcpy(logs[0], command);
}

void read_logs()
{
    char log_file[1024];
    sprintf(log_file, "%s/.shell_logs", home_dir);

    FILE *lf;
    lf = fopen(log_file, "r");

    log_count = 0;

    if (!lf)
    {
        fopen(log_file, "w"); // create if it doesn't already exist
    }
    else
    {
        char command[256];
        while (fgets(command, 256, lf))
        {
            command[strcspn(command, "\n")] = '\0';
            strcpy(logs[log_count++], command);
        }
    }
    fclose(lf);
}

void write_logs()
{
    char log_file[1024];
    sprintf(log_file, "%s/.shell_logs", home_dir);

    FILE *lf;
    lf = fopen(log_file, "w");

    if (!lf)
    {
        perror("~/.shell_logs");
    }
    else
    {
        for (int i = 0; i < log_count; i++)
        {
            fprintf(lf, "%s\n", logs[i]);
        }
    }
    fclose(lf);
}