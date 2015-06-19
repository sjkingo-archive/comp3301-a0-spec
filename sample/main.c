/* COMP3301 2011 - A0 Sample Solution
 * Sam Kingston, May 2011.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* prototypes from other .c files */
void do_ls(char *arg);
void do_lsr(char *arg);
void do_cp(char *src, char *dest);
void do_rm(char *arg);

static void dispatch_command(char *str)
{
    char *cmd = NULL, *arg1 = NULL, *arg2 = NULL;

    /* extract the arguments */
    cmd = strsep(&str, " ");
    if (cmd == NULL) {
        return;
    }
    arg1 = strsep(&str, " "); /* used by (optionally) ls and rm */
    arg2 = strsep(&str, " "); /* only used by cp */

    /* dispatch the work to the helper functions - note they should check the
     * arguments themselves to be non-NULL
     */
    if (strcmp(cmd, "ls") == 0) {
        do_ls(arg1);
    } else if (strcmp(cmd, "lsr") == 0) {
        do_lsr(arg1);
    } else if (strcmp(cmd, "cp") == 0) {
        do_cp(arg1, arg2);
    } else if (strcmp(cmd, "rm") == 0) {
        do_rm(arg1);
    } else {
        fprintf(stderr, "unrecognised command %s\n", cmd);
    }
}

int main(int argc, char **argv __attribute__((unused)))
{
    if (argc != 1) {
        fprintf(stderr, "shell takes no arguments\n");
        exit(1);
    }

    char buf[1024];
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        /* ignore blank lines */
        if (strlen(buf) <= 1 || buf[0] == ' ') {
            continue;
        }

        /* ignore too long lines */
        if (buf[strlen(buf)-1] != '\n') {
            fprintf(stderr, "Ignoring line longer than 1024 characters\n");
            continue;
        }
        buf[strlen(buf)-1] = '\0';
        dispatch_command(buf);
    }

    return 0;
}
