#include "consumer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "errExit.h"

#define MSG_BYTES 100

void consumer(int *pipeFD) {
  // close pipe's write end
  // ...

  ssize_t rB = -1;
  //+1 is for the '\0' character
  char buffer[MSG_BYTES + 1];
  do {
    // read max MSG_BYTES chars from the pipe
    // ...
    if (rB == -1)
      printf("<Consumer> it looks like the pipe is broken\n");
    else if (rB == 0)
      printf("<Consumer> it looks like all pipe's write ends were closed\n");
    else {
      // add '\0' to the end of the string
      // ...
      // print the line read from the pipe
      // ...
    }
  } while (rB > 0);

  // close pipe's read end
  // ...
}
