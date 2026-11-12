/* Demo 1 - a pipe between a parent and a child.
 *   ./pipe_demo        the engine (child) sends three moves, the arena
 *                      (parent) reads until the end of file
 *   ./pipe_demo keep   the arena keeps its copy of the write end open:
 *                      the end of file never comes (Ctrl+C to end it) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "errExit.h"

int main(int argc, char *argv[]) {
    int keep = argc > 1;
    int fd[2];
    if (pipe(fd) == -1)
        errExit("pipe");
    printf("pipe created: read end fd %d, write end fd %d\n", fd[0], fd[1]);
    fflush(stdout);

    pid_t pid = fork();
    if (pid == -1)
        errExit("fork");
    if (pid == 0) {
        // engine: writes, so it closes the read end
        close(fd[0]);
        const char *moves[] = {"bestmove e2e4\n", "bestmove g1f3\n", "bestmove f1b5\n"};
        for (int i = 0; i < 3; i++) {
            if (write(fd[1], moves[i], strlen(moves[i])) == -1)
                errExit("write");
            sleep(1);
        }
        close(fd[1]);   // the end of file for the reader... if nobody else holds a write end
        exit(0);
    }

    // arena: reads, so it closes the write end (unless told to keep it)
    if (!keep)
        close(fd[1]);
    else
        printf("arena: keeping the write end open (bad practice)\n");

    char buf[64];
    ssize_t n;
    while ((n = read(fd[0], buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';
        printf("arena read %zd bytes: %s", n, buf);
        fflush(stdout);
    }
    printf("arena: read returned %zd: end of file, the engine closed its end\n", n);
    close(fd[0]);
    wait(NULL);
    return 0;
}
