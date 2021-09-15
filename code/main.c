#include "prompt.h"
#include "headers.h"

char home_dir[1024];

int main()
{
    bool running = true;
    while (running)
    {
        getcwd(home_dir, 1024);

        prompt();
        char cmd[256];
        fgets(cmd, 256, stdin);
    }
}
