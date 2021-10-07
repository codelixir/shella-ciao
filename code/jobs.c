#include "headers.h"
#include "structs.h"
#include "jobs.h"

void jobs(int argc, char *argv[])
{
    bool flag_s = false, flag_r = false;
    // running/stopped processes

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (!strcmp(argv[i], "-rs") || !strcmp(argv[i], "-sr"))
            {
                flag_s = true;
                flag_r = true;
            }
            else if (!strcmp(argv[i], "-r"))
            {
                flag_r = true;
            }
            else if (!strcmp(argv[i], "-s"))
            {
                flag_s = true;
            }
            else
            {
                fprintf(stderr, "usage: jobs [-rs]\n");
                return;
            }
        }
    }
    else
    {
        flag_r = true;
        flag_s = true;
    }

    if (flag_r)
        show_jobs(true);
    if (flag_s)
        show_jobs(false);
}

void show_jobs(bool running)
{
    struct Node *duplicate = bg_proc_list->next;
    while (duplicate)
    {
        bool show = false;
        int proc_id = duplicate->id;

        char path_stat[64];
        char proc[64][64];
        sprintf(path_stat, "/proc/%d/stat", proc_id);
        FILE *f_stat = fopen(path_stat, "r");
        if (!f_stat)
        {
            perror(path_stat);
            continue;
        }
        else
        {
            fscanf(f_stat, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", proc[0], proc[1], proc[2], proc[3], proc[4], proc[5], proc[6], proc[7], proc[8], proc[9], proc[10], proc[11], proc[12], proc[13], proc[14], proc[15], proc[16], proc[17], proc[18], proc[19], proc[20], proc[21], proc[22], proc[23], proc[24], proc[25], proc[26], proc[27], proc[28], proc[29], proc[30], proc[31], proc[32], proc[33], proc[34], proc[35], proc[36], proc[37], proc[38], proc[39], proc[40], proc[41], proc[42], proc[43], proc[44], proc[45], proc[46], proc[47], proc[48], proc[49], proc[50], proc[51]);
            if (proc[2][0] == 'R')
            {
                show = running;
            }
            else if (proc[2][0] == 'S')
            {
                show = !running;
            }

            fclose(f_stat);
        }

        if (show)
        {
            char proc_status[16];
            if (running)
            {
                strcpy(proc_status, "Running");
            }
            else
            {
                strcpy(proc_status, "Stopped");
            }
            printf("[%d] %s %s [%d]\n", duplicate->j_num, proc_status, duplicate->name, proc_id);
        }

        duplicate = duplicate->next;
    }
}