#ifndef _FEED_HH
#define _FEED_HH

// The feed of the arena: a FIFO in the current directory (given)
#define FEED_FIFO "arena.fifo"
#define FEED_TIMEOUT 10     // seconds without moves: the feed closes

// A move on the feed
struct Move {
    int number;         // 1, 2, 3...
    char move[8];       // "e2e4", or "1-0", "0-1", "1/2" when the game is over
};

// Why the feed closed
#define CLOSED_BY_GAME_OVER 1
#define CLOSED_BY_TIMEOUT 2
#define CLOSED_BY_SIGINT 3

#endif
