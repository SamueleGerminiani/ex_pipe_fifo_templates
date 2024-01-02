#include "producer.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "errExit.h"

#define MSG_BYTES 100

struct Item {
  ssize_t size;
  char value[MSG_BYTES];
};

void producer(int *pipeFD, const char *filename) {
  // Close the read-end of the pipe
  //...

  printf("<Producer> text file: %s\n", filename);

  // Open the text file in read only mode
  int file = open(filename, O_RDONLY);
  if (file == -1) errExit("open failed");

  struct Item item;
  do {
    // read a chunk of bytes from file:
    // copy in item.value a chunk of bytes from the file, and
    // set item.size equal to the number of read bytes
    item.size = //...   
   

    if (item.size > 0) {
      // What is the right size?
      // (size of a ssize_t and the number of read chars)
      ssize_t bytes2send = sizeof(item.size) + item.size;
      // send struct item to Consumer through pipe
      //... 
      // check bW value
      if (bW != bytes2send) errExit("write failed");
    }
  } while (item.size > 0);

  // Close the write end of the pipe and the file
  //...
}
