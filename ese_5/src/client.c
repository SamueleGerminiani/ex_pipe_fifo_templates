#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "errExit.h"
#include "hints.h"
#include "report.h"

int main(int argc, char *argv[]) {
    // Check command line input arguments using 'argc'
    if (argc != 2) {
        printf("Usage: %s <position>\n", argv[0]);
        return 1;
    }

    // The reply FIFO of this client: its name from REPLY_FIFO_FORMAT and the
    // PID with 'snprintf'; create it using 'mkfifo' with the permissions
    // S_IRUSR | S_IWUSR (use 'errExit' if it fails)
    char replyName[64];



    // Fill the request: the PID of this process and the position from
    // argv[1] with 'atoi'
    struct Request req;



    // Open the request FIFO for writing ('open', O_WRONLY; it fails with
    // "No such file or directory" if the server is not running), write the
    // request in one 'write' (sizeof(req) bytes) and close it
    // (use 'errExit' if a call fails)
    int fd = -1;




    printf("client %d: hint requested for position %d\n", getpid(), req.position);

    // Open the reply FIFO for reading ('open', O_RDONLY: it blocks until the
    // server opens it for writing), read one struct Response with 'read'
    // (sizeof(resp) bytes, errExit on a short read) and close it
    struct Response resp;
    int reply = -1;




    printf("client %d: hint %s, score %+d\n", getpid(), resp.bestmove, resp.score);

    // Tournament report (given): reveals code #5 when the hint is right
    report_check(&req, &resp, replyName);

    // Remove the reply FIFO using 'unlink' (use 'errExit' if it fails)


    return 0;
}
