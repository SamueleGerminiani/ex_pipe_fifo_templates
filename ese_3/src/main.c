#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "errExit.h"
#include "report.h"

// The arena records a game: ./engine <moves> | grep bestmove, built with
// system calls as the shell does it

int main(int argc, char *argv[]) {
    // Check command line input arguments using 'argc'
    if (argc != 2) {
        printf("Usage: %s <moves>\n", argv[0]);
        return 1;
    }

    // Create the pipe using 'pipe' (use 'errExit' if it fails)
    int fd[2] = {-1, -1};


    // First command, the engine: create a child using 'fork'
    pid_t engine = -1;


    if (1 /*change this*/) {
        // Close the read end. Redirect the standard output to the write end:
        // close STDOUT_FILENO, then 'dup' the write end (the lowest free
        // descriptor is 1); close the write end, no longer needed




        // Replace the process with ./engine <moves> using 'execl'; if it
        // returns, it failed: 'errExit'


    }

    // Second command, grep: create a child using 'fork'
    pid_t filter = -1;


    if (1 /*change this*/) {
        // Close the write end. Redirect the standard input to the read end:
        // close STDIN_FILENO, 'dup' the read end (descriptor 0), close the
        // read end




        // Replace the process with grep bestmove using 'execlp' (it searches
        // the PATH); if it returns: 'errExit'


    }

    // Arena: close both ends. If the write end stayed open here, grep would
    // never see the end of file


    // Wait for both children using 'waitpid', collecting their status
    int engineStatus = 0, grepStatus = 0;



    printf("arena: engine exited with %d, grep with %d\n", WEXITSTATUS(engineStatus), WEXITSTATUS(grepStatus));

    // Tournament report (given): reveals code #3 when the pipeline worked
    report_check(fd, engineStatus, grepStatus);

    return 0;
}
