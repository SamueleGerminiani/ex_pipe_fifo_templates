#ifndef _REPORT_HH
#define _REPORT_HH

#include "hints.h"

/* Tournament report code: you do not need to read or modify this file :)
 *
 * report_check reveals code #5 when the response matches the request and
 * came through the reply FIFO of this client. Call it before removing
 * the reply FIFO. The code is bound to the current user and machine.
 */
void report_check(const struct Request *req, const struct Response *resp, const char *replyName);

#endif
