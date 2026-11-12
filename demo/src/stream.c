/* Demo 2 - a pipe is a byte stream: no message boundaries.
 * The engine writes three moves with three writes; the arena reads with one
 * read and gets them glued together. With a pause between the writes, each
 * read returns one move: what you get depends on timing, not on the writes. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "errExit.h"

int main(int argc, char *argv[]) {
    int pause = argc > 1;   // ./stream_demo pause
    int fd[2];
    if (pipe(fd) == -1)
        errExit("pipe");

    pid_t pid = fork();
    if (pid == -1)
        errExit("fork");
    if (pid == 0) {
        close(fd[0]);
        const char *moves[] = {"e2e4", "e7e5", "g1f3"};
        for (int i = 0; i < 3; i++) {
            if (write(fd[1], moves[i], strlen(moves[i])) == -1)
                errExit("write");
            if (pause)
                sleep(1);
        }
        close(fd[1]);
        exit(0);
    }

    close(fd[1]);
    sleep(pause ? 0 : 1);   // let the three writes land in the pipe
    char buf[100];
    ssize_t n;
    int reads = 0;
    while ((n = read(fd[0], buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';
        printf("read %d returned %zd bytes: \"%s\"\n", ++reads, n, buf);
        fflush(stdout);
    }
    printf("%d read(s) for 3 writes%s\n", reads, pause ? "" : ": the moves are glued together");
    close(fd[0]);
    wait(NULL);
    return 0;
}
