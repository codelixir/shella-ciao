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
        default: // '?'
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
        if (i)
            printf("\n");
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

        if (flag_l)
        {
            long_format(p_stat);
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
                    char f_path[2048];
                    sprintf(f_path, "%s/%s", path, f_name);
                    struct stat f_stat;
                    stat(f_path, &f_stat);
                    long_format(f_stat);
                }
                printf("%s\n", f_name);
            }
        }
    }
}

void long_format(struct stat f_stat)
{

    char perms[11];
    perms[0] = (S_ISDIR(f_stat.st_mode)) ? 'd' : '-';
    char rwx[3] = "rwx";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            perms[j + 3 * i + 1] = (f_stat.st_mode & (1 << (8 - 3 * i - j))) ? rwx[j] : '-';
    perms[10] = '\0';

    struct passwd *f_pw = getpwuid(f_stat.st_uid);
    struct group *f_gr = getgrgid(f_stat.st_gid);

    int n_link = f_stat.st_nlink;
    long f_size = f_stat.st_size;

    char time_str[32];
    struct tm filetime, today;

    time_t ft = f_stat.st_mtime, now = time(NULL);
    localtime_r(&ft, &filetime);
    localtime_r(&now, &today);

    if (withinSixMonths(filetime, today))
    {
        strftime(time_str, sizeof(time_str), "%b %e %H:%M", &filetime);
    }
    else
    {
        strftime(time_str, sizeof(time_str), "%b %e  %Y", &filetime);
    }

    printf("%s  %4d %16s %8s %16ld %s  ", perms, n_link, f_pw->pw_name, f_gr->gr_name, f_size, time_str);
}