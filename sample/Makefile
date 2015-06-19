CC=gcc
CFLAGS=-Wall -Wextra -Wshadow -Werror -std=gnu99 -O2 -D_GNU_SOURCE

.PHONY: all
all: shell

.PHONY: clean
clean:
	rm -f core *.o shell

shell: main.o ls.o lsr.o cp.o rm.o getdents.o
	$(CC) -o $@ $^
