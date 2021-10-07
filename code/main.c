#include "headers.h"
#include "structs.h"
#include "prompt.h"
#include "pipe.h"
#include "handlers.h"

pid_t shell_id;
int shell_stdout;
int shell_stdin;
char home_dir[1024];
char prev_dir[1024];
char logs[256][21];
int log_count;
bool running;
struct Node *bg_proc_list;
struct Vector open_files = {.count = 0};

int main()
{
    bg_proc_list = (struct Node *)malloc(sizeof(struct Node));
    bg_proc_list->id = -1;
    bg_proc_list->next = NULL;
    signal(SIGCHLD, bg_handler);

    shell_id = getpid();
    shell_stdin = dup(STDIN_FILENO);
    shell_stdout = dup(STDOUT_FILENO);

    getcwd(home_dir, 1024);
    strcpy(prev_dir, home_dir);

    running = true;
    printf("Ciao!\n");

    while (running)
    {
        prompt();

        char cmd[256];
        fgets(cmd, 256, stdin);

        char *tokenize = strtok(cmd, ";");
        char *commands[32];
        int cmd_num = 0;
        do
        {
            commands[cmd_num] = tokenize;
            tokenize = strtok(NULL, ";");
            cmd_num++;
        } while (tokenize != NULL);

        for (int i = 0; i < cmd_num; i++)
        {

            char *tokenize = strtok(commands[i], " \t\r\n");
            char *argv[32];
            int argc = 0;
            do
            {
                argv[argc++] = tokenize;
                tokenize = strtok(NULL, " \t\r\n");
            } while (tokenize != NULL);

            master(argc, argv);
        }
    }

    printf("Ciao!\n");

    return 0;
}
