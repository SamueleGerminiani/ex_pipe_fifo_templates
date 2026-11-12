#ifndef _REPORT_HH
#define _REPORT_HH

#include <stdlib.h>

/* Tournament report code: you do not need to read or modify this file :)
 *
 * report_check reveals code #1 when the arena received the whole book
 * through the pipe and closed both ends. Call it after closing them.
 * The code is bound to the current user and machine.
 */
void report_check(const int fd[2], const char *bookFile, const char *received, size_t bytes, int reads);

#endif
