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

/* prototype from ls.c */
void print_ls(char *arg);

static void print_lsr(char *arg)
{
    struct stat sb;
    if (lstat(arg, &sb) < 0) {
        perror("lstat");
        return;
    }

    if (S_ISDIR(sb.st_mode)) {
        printf("%s:\n", arg);
        do_getdents(arg, print_ls);
        printf("\n");
        do_getdents(arg, print_lsr); /* now recurse */
    }
}

void do_lsr(char *arg)
{
    if (arg == NULL) {
        arg = ".";
    }

    struct stat sb;
    if (lstat(arg, &sb) < 0) {
        perror("lstat");
        return;
    }

    if (!S_ISDIR(sb.st_mode)) {
        print_ls(arg);
    } else {
        print_lsr(arg);
    }
}
