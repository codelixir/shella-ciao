#include "headers.h"
#include "pinfo.h"
#include "utils.h"

void pinfo(int argc, char *argv[])
{

    pid_t proc_id;

    if (argc > 2)
    {
        printf("pinfo: Too many arguments\n");
        return;
    }
    else if (argc == 2)
    {
        proc_id = strtoi(argv[1]);
    }
    else
    {
        proc_id = shell_id;
    }

    char print_id[8];
    char print_status[4];
    char print_memory[32];
    char print_path[1024];

    bool plus = false;
    char path_stat[64], path_status[64], path_exe[64];
    sprintf(path_stat, "/proc/%d/stat", proc_id);
    sprintf(path_status, "/proc/%d/status", proc_id);
    sprintf(path_exe, "/proc/%d/exe", proc_id);

    // stat file
    char *line_stat = NULL;
    size_t len_stat;
    FILE *f_stat = fopen(path_stat, "r");

    if (!f_stat)
    {
        perror(path_stat);
        return;
    }
    else
    {
        char *buffer;
        long int proc_group, term_group;
        int i = 1;

        while (i && fscanf(f_stat, "%s", buffer))
        {
            switch (i)
            {
            case 5:
                proc_group = strtoi(buffer);
                break;
            case 8:
                term_group = strtoi(buffer);
                break;
            case 9:
                i = -1;
                break;
            default:
                break;
            }
            i++;
        }
        if (proc_group == term_group)
        {
            plus = true;
        }
        fclose(f_stat);
    }

    // status file
    char *line_status = NULL;
    size_t len_status;
    FILE *f_status = fopen(path_status, "r");

    if (!f_status)
    {
        perror(path_status);
        return;
    }
    else
    {
        int i = 1;
        while (i & (fgets(line_status, 0, f_status) > 0))
        {
            switch (i)
            {
            case 2:
            {
                char *tokenize = strtok(line_status, "\t ");
                tokenize = strtok(NULL, "\t ");
                strcpy(print_status, tokenize);
                break;
            }
            case 17:
            {
                char *tokenize = strtok(line_status, "\t ");
                tokenize = strtok(NULL, "\t ");
                strcpy(print_memory, tokenize);
                break;
            }
            case 18:
                i = -1;
                break;
            default:
                break;
            }

            i++;
        }
        if (plus)
        {
            print_status[1] = '+';
            print_status[2] = 0;
        }
        else
        {
            print_status[1] = 0;
        }
        fclose(f_status);
    }

    // exe file
    char buffer[1024];

    if (readlink(path_exe, buffer, 1024) <= 0)
    {
        perror(path_exe);
        return;
    }
    else
    {
        tildefy(print_path, buffer);
    }

    printf("pid -- %s\n", print_id);
    printf("Process Status -- %s\n", print_status);
    printf("memory -- %s\n", print_memory);
    printf("Executable Path -- %s\n", print_path);
}