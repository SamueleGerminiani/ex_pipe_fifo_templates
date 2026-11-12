#ifndef _REPORT_HH
#define _REPORT_HH

/* Tournament report code: you do not need to read or modify this file :)
 *
 * report_check reveals code #3 when both commands of the pipeline
 * terminated with status 0 and the arena closed both ends of the pipe.
 * Call it after waiting for both children.
 * The code is bound to the current user and machine.
 */
void report_check(const int fd[2], int engineStatus, int grepStatus);

#endif
