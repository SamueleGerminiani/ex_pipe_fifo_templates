#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "errExit.h"
#include "report.h"

#define CHUNK 100

int main(int argc, char *argv[]) {
    // Check command line input arguments using 'argc'
    if (argc != 2) {
        printf("Usage: %s <book file>\n", argv[0]);
        return 1;
    }

    // Create the pipe using 'pipe': fd[0] is the read end, fd[1] the write
    // end (use 'errExit' if it fails)
    int fd[2] = {-1, -1};


    // Create the engine process using 'fork'
    pid_t pid = -1;

    if (1 /*change this*/) {
        // fork failed: print a message using 'errExit'

    } else if (1 /*change this*/) {
        // Engine: close the read end, which it does not use


        // Open the book using 'open' and O_RDONLY (use 'errExit' if it fails)
        int book = -1;


        // Read the book in chunks of at most CHUNK bytes using 'read', and
        // write each chunk to the pipe using 'write': the bytes written must
        // be the bytes read (use 'errExit' otherwise). Stop when read
        // returns 0: the end of the book
        char chunk[CHUNK];
        ssize_t n;
        while (1 /*change this*/) {


        }


        // Close the book and the write end using 'close': the arena will see
        // the end of file. Terminate with 'exit'



    }

    // Arena: close the write end, which it does not use. As long as a write
    // end is open somewhere, the read end never sees the end of file


    printf("arena: loading the opening book from engine %d\n", pid);

    // Read from the pipe in chunks of at most CHUNK bytes using 'read' until
    // it returns 0 (the engine closed its end): append each chunk to
    // 'received' (given) and print it as it arrives with 'printf'
    static char received[8192];
    size_t bytes = 0;
    int reads = 0;
    char chunk[CHUNK];
    ssize_t n = 0;
    while (1 /*change this*/) {
        printf("%.*s", (int)n, chunk);
        if (bytes + n <= sizeof(received))
            memcpy(received + bytes, chunk, n);
        bytes += n;
        reads++;
    }


    printf("arena: end of file after %zu bytes in %d read(s)\n", bytes, reads);

    // Close the read end using 'close' and wait for the engine using 'wait'



    // Tournament report (given): reveals code #1 when the whole book arrived
    report_check(fd, argv[1], received, bytes, reads);

    return 0;
}
