#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "errExit.h"
#include "hints.h"

// Requests served so far, for the handler
volatile int served = 0;

// The handler of SIGINT: the server stops from here, because a blocked
// open or read on the FIFO resumes after the handler returns. Print
// "hint server: stopped after <served> request(s)", remove the request
// FIFO with 'unlink' and terminate with 'exit'
void sigHandler(int sig) {



}

int main(int argc, char *argv[]) {
    // Install sigHandler for SIGINT using 'signal' (errExit on SIG_ERR)


    // Create the request FIFO using 'mkfifo' with the name HINTS_FIFO and
    // the permissions S_IRUSR | S_IWUSR (use 'errExit' if it fails)


    printf("hint server %d: waiting for requests on %s, Ctrl+C to stop\n", getpid(), HINTS_FIFO);
    fflush(stdout);

    while (1) {
        // Open the request FIFO for reading ('open', O_RDONLY): it blocks
        // until a client opens it for writing (use 'errExit' if it fails)
        int fd = -1;



        // Read one struct Request using 'read' (errExit on -1), then close
        // the FIFO. Less than sizeof(req) bytes: the client closed without
        // a full request, go on with the next one
        struct Request req;
        ssize_t n = -1;







        // Compute the hint with hintFor (given)
        struct Response resp;
        hintFor(req.position, &resp);
        printf("request from client %d: position %d -> %s (%+d)\n", (int)req.cPid, req.position, resp.bestmove, resp.score);
        fflush(stdout);

        // The reply FIFO of the client: its name from REPLY_FIFO_FORMAT and
        // req.cPid with 'snprintf'. Open it for writing ('open', O_WRONLY),
        // write the response in one 'write' (sizeof(resp) bytes) and close
        // it (use 'errExit' if a call fails)
        char replyName[64];

        int reply = -1;





        served++;
    }

    return 0;
}
