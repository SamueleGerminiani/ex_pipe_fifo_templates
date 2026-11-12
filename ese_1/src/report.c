/* Tournament report code: you do not need to read or modify this file :)
 *
 * The confirmation code is encrypted: it can only be decrypted with a key
 * computed from the correct result of the exercise.
 * The revealed code is bound to the current user and machine.
 */
#include "report.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FNV_START 2166136261u

static unsigned int mix(unsigned int h, unsigned int v) {
    for (int i = 0; i < 4; i++) {
        h ^= (v >> (8 * i)) & 0xff;
        h *= 16777619u;
    }
    return h;
}

static unsigned int next_byte(unsigned int *s) {
    *s ^= *s << 13;
    *s ^= *s >> 17;
    *s ^= *s << 5;
    return *s & 0xff;
}

/* Decrypts 'len' bytes of 'enc' into 'out' and returns its checksum */
static unsigned int decrypt(unsigned int key, const unsigned char *enc, int len, char *out) {
    unsigned int s = key ? key : 1;
    unsigned int h = FNV_START;
    for (int i = 0; i < len; i++) {
        out[i] = enc[i] ^ next_byte(&s);
        h = mix(h, (unsigned char)out[i]);
    }
    out[len] = '\0';
    return h;
}

/* Appends to 'word' a code bound to the current user and machine */
static void bind_to_user(char *out, size_t size, const char *word) {
    const char *user = getenv("USER");
    char host[256] = "";
    char id[600];

    if (user == NULL || user[0] == '\0')
        user = "unknown";
    if (gethostname(host, sizeof(host)) != 0 || host[0] == '\0')
        strcpy(host, "unknown");
    host[sizeof(host) - 1] = '\0';

    snprintf(id, sizeof(id), "%s:%s@%s", word, user, host);
    unsigned int h = FNV_START;
    for (const char *c = id; *c != '\0'; c++) {
        h ^= (unsigned char)*c;
        h *= 16777619u;
    }
    snprintf(out, size, "%s-%04X", word, h & 0xffff);
}

static void reveal(int number, unsigned int key, const unsigned char *enc, int len, unsigned int check) {
    char word[32];
    char bound[48];
    if (decrypt(key, enc, len, word) != check)
        return;
    bind_to_user(bound, sizeof(bound), word);
    printf("\n*** Tournament report, code #%d of 5: \"%s\" ***\n", number, bound);
    fflush(stdout);
}

/* 1 if the descriptor is closed in this process */
__attribute__((unused)) static int is_closed(int fd) {
    return fcntl(fd, F_GETFD) == -1 && errno == EBADF;
}

/* Code #1: the arena received exactly the content of the book, in at least
 * one read, saw the end of file, and both ends of the pipe are closed */
void report_check(const int fd[2], const char *bookFile, const char *received, size_t bytes, int reads) {
    static const unsigned char enc[] = {0xc8, 0x57, 0x4b, 0x69, 0x95};
    static char book[8192];
    int ok = fd != NULL && bookFile != NULL && received != NULL && reads >= 1;
    if (ok) {
        int f = open(bookFile, O_RDONLY);
        ssize_t n = (f == -1) ? -1 : read(f, book, sizeof(book));
        if (f != -1)
            close(f);
        if (n <= 0 || (size_t)n != bytes || memcmp(book, received, bytes) != 0)
            ok = 0;
    }
    if (ok && !(is_closed(fd[0]) && is_closed(fd[1])))
        ok = 0;
    unsigned int key = mix(mix(FNV_START, 0x71), ok);
    reveal(1, key, enc, sizeof(enc), 0x2cb1a6f4u);
}
