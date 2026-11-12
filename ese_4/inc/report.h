#ifndef _REPORT_HH
#define _REPORT_HH

/* Tournament report code: you do not need to read or modify this file :)
 *
 * report_check reveals code #4 when the feed received at least two moves
 * and closed because of the timeout. Call it before removing the FIFO.
 * The code is bound to the current user and machine.
 */
void report_check(const char *fifoName, int moves, int reason);

#endif
