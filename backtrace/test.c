#include <signal.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

static int i = 0;

void helper()
{
    ++i;
    helper();
}

void print_trace(int sig)
{
    void *array[10];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace(array, 10);
    strings = backtrace_symbols(array, size);

    printf("Obtained %zd stack frames.\n", size);

    for (i = 0; i < size; ++i)
        printf("%s\n", strings[i]);

    free (strings);
    exit(EXIT_FAILURE);
}

int main(int argc, const char *argv[])
{
    signal(SIGSEGV, print_trace);
    helper();
    return 0;
}
