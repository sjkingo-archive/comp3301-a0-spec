/* COMP3301 2011 - A0 Sample Solution
 * Sam Kingston, May 2011.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void do_cp(char *src, char *dest)
{
    int src_fd = -1, dest_fd = -1;
    struct stat src_stat, dest_stat;
    bool free_path = false;
    char *path = dest;

    if (src == NULL || dest == NULL) {
        fprintf(stderr, "invalid arguments to cp\n");
        return;
    }

    if ((src_fd = open(src, O_RDONLY)) < 0) {
        perror("open");
        return;
    }
    if (fstat(src_fd, &src_stat) < 0) {
        perror("fstat");
        goto close;
    }

    /* ensure we are trying to copy a regular file */
    if (!S_ISREG(src_stat.st_mode)) {
        fprintf(stderr, "unsupported source file type\n");
        goto close;
    }

    if (lstat(dest, &dest_stat) == 0) {
        /* if a directory is given, construct the path name so we can copy
         * into it
         */
        if (S_ISDIR(dest_stat.st_mode)) {
            char *b = basename(src);
            path = malloc(strlen(dest) + 1 + strlen(b) + 1);
            sprintf(path, "%s/%s", dest, b);
            free_path = true;
        } else if (S_ISREG(dest_stat.st_mode)) {
            /* do nothing; path already equals dest */
        } else {
            fprintf(stderr, "unsupported destination file type\n");
            goto close;
        }
    }

    /* open the destination file for writing: creating it if it doesn't exist,
     * and truncating it if it does
     */
    if ((dest_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, src_stat.st_mode)) < 0) {
        perror("open");
        goto close;
    }

    /* copy the file in chunks */
    char buf[1024];
    ssize_t bytes;
    while ((bytes = read(src_fd, buf, sizeof(buf))) > 0) {
        if (write(dest_fd, buf, bytes) < 0) {
            perror("write");
            goto close;
        }
    }
    if (bytes == -1) {
        perror("read");
        goto close;
    }

close:
    if (free_path) {
        free(path);
    }
    if (src_fd != -1) {
        close(src_fd);
    }
    if (dest_fd != -1) {
        close(dest_fd);
    }
    return;
}
