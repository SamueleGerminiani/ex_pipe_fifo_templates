#ifndef _REPORT_HH
#define _REPORT_HH

#include <sys/types.h>

/* Tournament report code: you do not need to read or modify this file :)
 *
 * report_record is called by the arena for every record received.
 * report_check reveals code #2 when every record arrived whole and both
 * ends are closed. Call it after closing them and waiting for the engines.
 * The code is bound to the current user and machine.
 */
void report_record(const char *value, ssize_t size);
void report_check(const int fd[2], int expected);

#endif
