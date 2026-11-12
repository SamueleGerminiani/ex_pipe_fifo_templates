/* A chess engine, as the arena sees it (given): it prints what a real
 * engine prints on its standard output, in the UCI protocol: search
 * information lines, then the move it chose. Usage: ./engine <moves> */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "moves.h"

int main(int argc, char *argv[]) {
    int moves = (argc > 1) ? atoi(argv[1]) : 6;
    if (moves <= 0 || moves > OPENING_MOVES)
        moves = OPENING_MOVES;
    printf("id name Arena Engine 1.0\n");
    for (int i = 0; i < moves; i++) {
        for (int depth = 1; depth <= 3; depth++)
            printf("info depth %d score cp %d nodes %d\n", depth, (i * 13) % 50 - 20, depth * 1000 + i);
        printf("bestmove %s\n", opening[i]);
    }
    return 0;
}
