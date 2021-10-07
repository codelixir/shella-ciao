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
        fprintf(stderr, "pinfo: Too many arguments\n");
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
        char proc[64][64];
        fscanf(f_stat, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", proc[0], proc[1], proc[2], proc[3], proc[4], proc[5], proc[6], proc[7], proc[8], proc[9], proc[10], proc[11], proc[12], proc[13], proc[14], proc[15], proc[16], proc[17], proc[18], proc[19], proc[20], proc[21], proc[22], proc[23], proc[24], proc[25], proc[26], proc[27], proc[28], proc[29], proc[30], proc[31], proc[32], proc[33], proc[34], proc[35], proc[36], proc[37], proc[38], proc[39], proc[40], proc[41], proc[42], proc[43], proc[44], proc[45], proc[46], proc[47], proc[48], proc[49], proc[50], proc[51]);
        strcpy(proc_status, proc[2]);
        strcpy(proc_memory, proc[22]);
        int proc_group = strtoi(proc[4]), term_group = strtoi(proc[7]);

        if (proc_group == term_group)
        {
            proc_status[1] = '+';
            proc_status[2] = 0;
        }
        else
        {
            proc_status[1] = 0;
        }
        fclose(f_stat);
    }

    // exe file
    char buffer[1024] = "";

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