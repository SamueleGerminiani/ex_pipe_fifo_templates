/* Demo 3 - what the shell does for "ls -l | wc -l": a pipe, two children,
 * the standard output of the first and the standard input of the second
 * redirected with dup, two exec. The parent closes both ends and waits. */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "errExit.h"

int main(int argc, char *argv[]) {
    int fd[2];
    if (pipe(fd) == -1)
        errExit("pipe");

    pid_t first = fork();
    if (first == -1)
        errExit("fork");
    if (first == 0) {
        close(fd[0]);
        close(STDOUT_FILENO);   // 1 is free...
        dup(fd[1]);             // ...and dup takes the lowest free descriptor: 1
        close(fd[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
        errExit("execlp ls");
    }

    pid_t second = fork();
    if (second == -1)
        errExit("fork");
    if (second == 0) {
        close(fd[1]);
        close(STDIN_FILENO);    // 0 is free...
        dup(fd[0]);             // ...so the read end becomes the standard input
        close(fd[0]);
        execlp("wc", "wc", "-l", (char *)NULL);
        errExit("execlp wc");
    }

    // the parent holds both ends: if it kept the write end, wc would wait forever
    close(fd[0]);
    close(fd[1]);
    waitpid(first, NULL, 0);
    waitpid(second, NULL, 0);
    printf("(that was ls -l | wc -l, built with pipe, fork, dup and exec)\n");
    return 0;
}
