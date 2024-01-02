#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "consumer.h"
#include "errExit.h"
#include "producer.h"

int main(int argc, char *argv[]) {
  // Check command line input arguments.
  if (argc == 1) {
    printf("Usage: %s textFile1 ... textFileN\n", argv[0]);
    return 0;
  }

  int pipeFD[2];

  // Make a new PIPE
  if (pipe(pipeFD) == -1) errExit("pipe failed");

  // Generate a sub process for each input text file, run the producer
  printf("<Consumer> making %d subprocesses...\n", (argc - 1));
  for (int i = 0; i < (argc - 1); ++i) {
    //...
  }

  // run the consumer process, which reads the pipe
  consumer(pipeFD);

  // wait the termination of all child process.
  //...
}
