#include "headers.h"
#include "prompt.h"
#include "execute.h"

char home_dir[1024];
char prev_dir[1024];
bool running;

int main()
{
    getcwd(home_dir, 1024);
    strcpy(prev_dir, home_dir);
    running = true;

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

            execute(argc, argv);
        }
    }
}
