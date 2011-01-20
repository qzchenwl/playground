#ifndef PG_SOCK_HELP
#define PG_SOCK_HELP

#include <unistd.h>
#define LISTENQ (1024)

ssize_t Readline(int fd, void *vptr, size_t maxlen);
ssize_t Writeline(int fd, const void *vptr, size_t maxlen);

#endif
