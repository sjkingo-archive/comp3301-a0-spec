/* COMP3301 2011 - A0 Sample Solution
 * Sam Kingston, May 2011.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* prototype from getdents.c */
void do_getdents(char *dir, void (*)(char *));

void do_rm(char *arg)
{
    if (arg == NULL) {
        fprintf(stderr, "invalid arguments to rm\n");
        return;
    }

    struct stat sb;
    if (lstat(arg, &sb) < 0) {
        perror("lstat");
        return;
    }

    if (S_ISREG(sb.st_mode) || S_ISLNK(sb.st_mode)) {
        /* unlink a single file */
        if (unlink(arg) < 0) {
            perror("unlink");
            return;
        }
    } else if (S_ISDIR(sb.st_mode)) {
        /* recursively remove the directory tree */
        do_getdents(arg, do_rm);
        if (rmdir(arg) < 0) {
            perror("rmdir");
            return;
        }
    } else {
        fprintf(stderr, "filename given is not a supported type\n");
        return;
    }


}
