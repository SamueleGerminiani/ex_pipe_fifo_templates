#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "errExit.h"
#include "feed.h"

int main(int argc, char *argv[]) {
    // Check command line input arguments using 'argc'
    if (argc != 3) {
        printf("Usage: %s <number> <move>   (e.g. %s 1 e2e4, or 40 1-0)\n", argv[0], argv[0]);
        return 1;
    }

    // Fill the move: the number from argv[1] with 'atoi', the move from
    // argv[2] copied with 'strncpy' (at most sizeof(mv.move) - 1 characters,
    // then the terminator)
    struct Move mv;
    mv.number = 0;



    // Open the FIFO for writing using 'open' and O_WRONLY: it blocks until
    // the feed opens it for reading; it fails with "No such file or
    // directory" if the feed is not running (use 'errExit')
    int fd = -1;


    // Write the move using 'write': sizeof(mv) bytes, in one write
    // (use 'errExit' if it writes less), then close the FIFO



    printf("move %d (%s) sent to the feed\n", mv.number, mv.move);
    return 0;
}
