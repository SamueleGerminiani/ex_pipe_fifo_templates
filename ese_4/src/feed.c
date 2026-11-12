#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "errExit.h"
#include "feed.h"
#include "report.h"

// Moves received so far, for the handler
volatile int moves = 0;

// The handler of SIGALRM (no move for FEED_TIMEOUT seconds) and SIGINT
// (the operator stops the feed): the feed closes from here, because a
// blocked open or read on the FIFO resumes after the handler returns.
// Print "feed: no moves for a while" or "feed: stopped by the operator",
// call report_check (given) with the reason CLOSED_BY_TIMEOUT or
// CLOSED_BY_SIGINT, remove the FIFO with 'unlink' and terminate with 'exit'
void sigHandler(int sig) {




}

int main(int argc, char *argv[]) {
    // Install sigHandler for SIGALRM and SIGINT using 'signal'
    // (use 'errExit' if it returns SIG_ERR)


    // Create the FIFO using 'mkfifo' with the name FEED_FIFO and the
    // permissions S_IRUSR | S_IWUSR (use 'errExit' if it fails: a leftover
    // FIFO of a previous run must be removed with rm)


    printf("feed %d: waiting for moves on %s (%d seconds, or Ctrl+C)\n", getpid(), FEED_FIFO, FEED_TIMEOUT);
    fflush(stdout);

    int gameOver = 0;
    while (!gameOver) {
        // Arm the timeout using 'alarm' with FEED_TIMEOUT seconds: a move
        // must arrive before it expires, or the handler closes the feed


        // Open the FIFO for reading using 'open' and O_RDONLY: it blocks
        // until a client opens it for writing (use 'errExit' if it fails)
        int fd = -1;



        // Read one struct Move using 'read' (use 'errExit' if it fails).
        // sizeof(struct Move) bytes: a move, print "move <number>: <move>"
        // and count it; if the move is "1-0", "0-1" or "1/2" the game is
        // over. 0 bytes: the client closed without writing, nothing to do.
        // Then close the FIFO
        struct Move mv;
        ssize_t n = -1;


        if (n == sizeof(mv)) {
            printf("move %d: %s\n", mv.number, mv.move);
            fflush(stdout);
            moves++;


        }


    }

    // Cancel the timeout using 'alarm' with 0


    printf("feed: game over, closing after %d move(s)\n", moves);

    // Tournament report (given): reveals code #4 only when the feed timed
    // out (from the handler); here the game is over, no code
    report_check(FEED_FIFO, moves, CLOSED_BY_GAME_OVER);

    // Remove the FIFO using 'unlink' (use 'errExit' if it fails)


    return 0;
}
