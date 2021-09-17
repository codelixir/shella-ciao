#include "headers.h"
#include "ls.h"
#include "utils.h"

void ls(int argc, char *argv[])
{
    optind = 1;
    bool flag_l = false, flag_a = false;
    int opt;

    while ((opt = getopt(argc, argv, "la")) != -1)
    {
        switch (opt)
        {
        case 'a':
            flag_a = true;
            break;
        case 'l':
            flag_l = true;
            break;
        default: /* '?' */
            printf("usage: ls [-al] [file...]\n");
        }
    }

    char *file_v[32];
    int file_c = 0;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            file_v[file_c++] = argv[i];
        }
    }

    if (!file_c)
    {
        char cwd[1024];
        getcwd(cwd, 1024);
        file_v[0] = cwd;
        file_c = 1;
    }

    for (int i = 0; i < file_c; i++)
    {
        list(file_v[i], flag_l, flag_a, file_c - 1);
    }
}

void list(char *file, bool flag_l, bool flag_a, bool multiple)
{
    char path[1024];
    untildefy(path, file);

    struct stat p_stat;
    stat(path, &p_stat);

    if (!S_ISDIR(p_stat.st_mode))
    { // not a directory
        mode_t p_mode = p_stat.st_mode;
        if (flag_l)
        {
            // something
        }
        printf("%s\n", path);
    }
    else
    { // is a directory
        if (multiple)
        {
            printf("\n%s:\n", path);
        }
        struct dirent **files;
        int num_files = scandir(path, &files, NULL, alphasort);
        if (num_files < 0)
        {
            perror(path);
            return;
        }
        else
        {
            for (int i = 0; i < num_files; i++)
            {
                struct dirent *fl = files[i];
                char *f_name = fl->d_name;
                if (!flag_a && (f_name[0] == '.'))
                    continue;
                if (flag_l)
                {
                    // something
                }
                printf("%s\n", f_name);
            }
        }
    }
}
