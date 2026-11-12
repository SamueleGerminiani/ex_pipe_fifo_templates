# Pipes and FIFOs: lab templates

The chess engine arena. A chess GUI talks to its engines through pipes on
their standard input and output; the arena of the department runs
tournaments, records games, broadcasts the moves and answers requests for
hints, all through pipes and FIFOs. Each exercise is one channel of the
arena, written from a partially completed template.

```
ex_pipe_fifo_templates/
├── demo/      <- Part 1: the programs shown during the lecture
├── ese_1/     <- Exercise 1: the opening book (a pipe between parent and child)
├── ese_2/     <- Exercise 2: the tournament (several engines on one pipe)
├── ese_3/     <- Exercise 3: recording the game (a pipeline with dup and exec)
├── ese_4/     <- Exercise 4: the feed (a FIFO with a timeout)
├── ese_5/     <- Exercise 5: the hint server (request and reply FIFOs)
└── report/    <- the tournament report (needs the 5 confirmation codes)
```

The exercises are independent: solve them in any order.

To compile:
> cd ese_1
> make

To run the executable
> ./arena book.txt

To remove object file(s) and executable(s)
> make clean

A FIFO left behind by a crashed run is a file: ls -l shows it with a 'p',
rm removes it.

To file the tournament report
> ./report/file_report.sh

It can be filed only with the 5 confirmation codes: exercise N reveals
code N when its result is the expected one.
