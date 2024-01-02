#include "producer.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "errExit.h"

#define MSG_BYTES 100

void producer(int *pipeFD, const char *filename) {
  // Close the read-end of the pipe
  // ...

  printf("<Producer> text file: %s\n", filename);

  // open filename for reading only
  int file = open(filename, O_RDONLY);
  if (file == -1) errExit("open failed");

  char buffer[MSG_BYTES];
  ssize_t bR, bW = -1;
  do {
    // read max MSG_BYTES chars from the file
    // ...

    if (bR > 0) {
      // write bR chars to the pipe
      // ...
    }
  } while (bR > 0);

  // Close the write end of the pipe and pipe
  // ...
}
