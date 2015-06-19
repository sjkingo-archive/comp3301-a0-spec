/* COMP3301 2011 - A0 Sample Solution
 * Sam Kingston, May 2011.
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* prototype from getdents.c */
void do_getdents(char *dir, void (*)(char *));

void print_ls(char *arg)
{
    struct stat sb;
    if (lstat(arg, &sb) < 0) {
        perror("lstat");
        return;
    }

    char type;
    if (S_ISREG(sb.st_mode)) {
        type = 'f';
    } else if (S_ISDIR(sb.st_mode)) {
        type = 'd';
    } else if (S_ISLNK(sb.st_mode)) {
        type = 's';
    } else {
        type = 'o';
    }

    printf("%c% 10lld %s\n", type, (long long)sb.st_size, basename(arg));
}

void do_ls(char *arg)
{
    if (arg == NULL) {
        arg = ".";
    }

    struct stat sb;
    if (lstat(arg, &sb) < 0) {
        perror("lstat");
        return;
    }

    if (S_ISDIR(sb.st_mode)) {
        do_getdents(arg, print_ls);
    } else {
        print_ls(arg);
    }
}
