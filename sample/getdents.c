/* COMP3301 2011 - A0 Sample Solution
 * Sam Kingston, May 2011.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <unistd.h>

struct linux_dirent {
    long d_ino;
    off_t d_off;
    unsigned short d_reclen;
    char d_name[];
};

void do_getdents(char *dir, void (*callback)(char *))
{
    int fd;
    if ((fd = open(dir, O_RDONLY | O_DIRECTORY)) < 0) {
        perror("open");
        return;
    }

    while (1) {
        char buf[1024];
        int nread;

        /* make the system call and fetch 1024 bytes worth of entries */
        nread = syscall(SYS_getdents, fd, buf, sizeof(buf));
        if (nread < 0) {
            perror("getdents");
            break;
        }

        /* no more entries to return */
        if (nread == 0) {
            break;
        }

        int bpos = 0;
        while (bpos < nread) {
            /* fetch the current entry and move to the next */
            struct linux_dirent *d = (struct linux_dirent *)(buf + bpos);
            bpos += d->d_reclen;

            /* ignore . and .. */
            char *name = (char *)d->d_name;
            if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
                continue;
            }

            /* construct the path and call back the function */
            char *path = malloc(strlen(dir) + 1 + strlen(name) + 1);
            sprintf(path, "%s/%s", dir, name);
            callback(path);
            free(path);
        }
    }

    close(fd);
}
