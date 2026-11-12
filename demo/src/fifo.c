/* Demo 4 - a FIFO: a pipe with a name in the filesystem.
 *   terminal 1:  ./fifo_demo reader     creates demo.fifo and opens it for reading
 *   terminal 2:  ./fifo_demo writer     opens it for writing and sends moves
 * open blocks until the other end is opened by somebody: watch the order. */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "errExit.h"

#define FIFO "demo.fifo"

int main(int argc, char *argv[]) {
    if (argc != 2 || (strcmp(argv[1], "reader") != 0 && strcmp(argv[1], "writer") != 0)) {
        printf("Usage: %s reader | writer\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "reader") == 0) {
        if (mkfifo(FIFO, S_IRUSR | S_IWUSR) == -1)
            errExit("mkfifo (rm demo.fifo if it is left from a previous run)");
        printf("reader: %s created (ls -l shows a 'p'); opening for reading...\n", FIFO);
        fflush(stdout);
        int fd = open(FIFO, O_RDONLY);          // blocks until a writer opens it
        if (fd == -1)
            errExit("open");
        printf("reader: a writer arrived\n");
        char buf[64];
        ssize_t n;
        while ((n = read(fd, buf, sizeof(buf) - 1)) > 0) {
            buf[n] = '\0';
            printf("reader got: %s", buf);
            fflush(stdout);
        }
        printf("reader: end of file, the writer closed; removing %s\n", FIFO);
        close(fd);
        if (unlink(FIFO) == -1)
            errExit("unlink");
    } else {
        printf("writer: opening %s for writing...\n", FIFO);
        fflush(stdout);
        int fd = open(FIFO, O_WRONLY);          // blocks until a reader opens it
        if (fd == -1)
            errExit("open (is the reader running?)");
        printf("writer: a reader is there, sending three moves\n");
        const char *moves[] = {"move 1: e2e4\n", "move 2: e7e5\n", "move 3: g1f3\n"};
        for (int i = 0; i < 3; i++) {
            if (write(fd, moves[i], strlen(moves[i])) == -1)
                errExit("write");
            sleep(1);
        }
        close(fd);
        printf("writer: done\n");
    }
    return 0;
}
