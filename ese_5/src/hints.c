#include "hints.h"

#include <string.h>

#include "moves.h"

void hintFor(int position, struct Response *resp) {
    strcpy(resp->bestmove, opening[(position < 0 ? -position : position) % OPENING_MOVES]);
    resp->score = (position * 37) % 200 - 100;
}
