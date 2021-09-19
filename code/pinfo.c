#include "headers.h"
#include "pinfo.h"
#include "utils.h"

void pinfo(int argc, char *argv[])
{

    pid_t proc_id;
    char proc_status[4];
    char proc_memory[32];
    char proc_path[1024];

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

    bool plus = false;
    char path_stat[64], path_status[64], path_exe[64];
    sprintf(path_stat, "/proc/%d/stat", proc_id);
    sprintf(path_status, "/proc/%d/status", proc_id);
    sprintf(path_exe, "/proc/%d/exe", proc_id);

    // stat file
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
    char line_status[256];
    FILE *f_status = fopen(path_status, "r");

    if (!f_status)
    {
        perror(path_status);
        return;
    }
    else
    {
        int i = 1;
        while (i & (fgets(line_status, 256, f_status) > 0))
        {
            switch (i)
            {
            case 2:
            {
                char *tokenize = strtok(line_status, "\t ");
                tokenize = strtok(NULL, "\t ");
                strcpy(proc_status, tokenize);
                break;
            }
            case 17:
            {
                char *tokenize = strtok(line_status, "\t ");
                tokenize = strtok(NULL, "\t ");
                strcpy(proc_memory, tokenize);
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
            proc_status[1] = '+';
            proc_status[2] = 0;
        }
        else
        {
            proc_status[1] = 0;
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
        tildefy(proc_path, buffer);
    }

    printf("pid -- %d\n", proc_id);
    printf("Process Status -- %s\n", proc_status);
    printf("memory -- %s\n", proc_memory);
    printf("Executable Path -- %s\n", proc_path);
}