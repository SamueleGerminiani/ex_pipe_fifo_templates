#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "errExit.h"
#include "moves.h"
#include "report.h"

#define ENGINES 4
#define MOVES_EACH 5
#define VALUE_SIZE 64

const char *engineName[ENGINES] = {"Stockfish", "Komodo", "Leela", "Ethereal"};

// A record on the pipe: its size first, then the bytes (given). Written in
// one write, which is atomic for less than PIPE_BUF bytes, a record can
// never be mixed with the record of another engine
struct Item {
    ssize_t size;            // bytes used in value, terminator included
    char value[VALUE_SIZE];
};

int main(int argc, char *argv[]) {
    // Check command line input arguments using 'argc'
    if (argc != 2) {
        printf("Usage: %s <engines, 1 to %d>\n", argv[0], ENGINES);
        return 1;
    }

    // Convert argv[1] to an integer using 'atoi': the engines of the tournament
    int engines = 0;
    if (engines <= 0 || engines > ENGINES) {
        printf("The number of engines must be between 1 and %d!\n", ENGINES);
        return 1;
    }

    // Create the pipe using 'pipe' (use 'errExit' if it fails)
    int fd[2] = {-1, -1};


    // Create the engines using 'fork'
    for (int e = 0; e < engines; e++) {
        pid_t pid = -1;

        if (1 /*change this*/) {
            // fork failed: print a message using 'errExit'

        } else if (1 /*change this*/) {
            // Engine e: close the read end, then send MOVES_EACH records:
            // value is "<name>: <move>" (given), size is its length plus the
            // terminator; write size + sizeof(size) bytes of the item in one
            // 'write' (use 'errExit' if it writes less). Then close the
            // write end and terminate with 'exit'

            struct Item item;
            for (int m = 0; m < MOVES_EACH; m++) {
                snprintf(item.value, VALUE_SIZE, "%s: %s", engineName[e], opening[(e + 2 * m) % OPENING_MOVES]);



                usleep(1000);   // a little thinking time (given)
            }


        }
        // Arena: keep creating engines
    }

    // Arena: close the write end, which it does not use


    // Receive the records until the end of file: read the size field first
    // (sizeof(size) bytes; 0 bytes read: every engine closed its end), then
    // exactly size bytes of value. Print "[<size> bytes] <value>" and call
    // report_record (given) for each record (use 'errExit' on a short read)
    int records = 0;
    struct Item item;
    while (1 /*change this*/) {






        printf("[%zd bytes] %s\n", item.size, item.value);
        report_record(item.value, item.size);
        records++;
    }

    printf("arena: end of file after %d records from %d engine(s)\n", records, engines);

    // Close the read end using 'close' and wait for every engine using 'wait'



    // Tournament report (given): reveals code #2 when every record arrived whole
    report_check(fd, engines * MOVES_EACH);

    return 0;
}
