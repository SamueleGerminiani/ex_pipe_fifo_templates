#include "consumer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "errExit.h"

#define MSG_BYTES 100

void consumer(int *pipeFD) {
  // close pipe's write end
  //...

  ssize_t rB = -1;
  char buffer[MSG_BYTES + 1];
  do {
    // read the chunk size
    ssize_t size;
    //...
    if (rB == -1)
      printf("<Consumer> it looks like the pipe is broken\n");
    else if (rB == 0)
      printf("<Consumer> it looks like all pipe's write ends were closed\n");
    else if (rB != sizeof(ssize_t))
      printf("<Consumer> it looks like there is not \n");
    else {
      // read the byte chunk sent by a Producer
      //...
      if (rB == -1)
        printf("<Consumer> it looks like the pipe is broken\n");
      else if (rB == 0)
        printf("<Consumer> it looks like all pipe's write ends were closed\n");
      else if (rB != size)
        printf("<Consumer> it looks like there is not \n");
      else {
        buffer[size] = '\0';
        printf("<Consumer> line: %s\n", buffer);
      }
    }
  } while (rB > 0);

  // close pipe's read end
  //...
}
