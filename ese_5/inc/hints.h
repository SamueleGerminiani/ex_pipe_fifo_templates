#ifndef _HINTS_HH
#define _HINTS_HH

#include <sys/types.h>

// The hint server of the arena (given): a request FIFO for everybody, a
// reply FIFO per client, named after its PID
#define HINTS_FIFO "hints.fifo"
#define REPLY_FIFO_FORMAT "hint_reply.%d"   // e.g. hint_reply.4312

struct Request {        // client -> server
    pid_t cPid;         // the client, which owns the reply FIFO
    int position;       // the position to analyse: a number, for simplicity
};

struct Response {       // server -> client
    char bestmove[8];
    int score;          // centipawns, positive for white
};

// hintFor computes the hint for a position (given)
void hintFor(int position, struct Response *resp);

#endif
