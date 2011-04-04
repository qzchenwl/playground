#include <unistd.h>
#include <signal.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

void print_trace()
{
    void *array[10];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace(array, 10);
    strings = backtrace_symbols (array, size);

    printf("Obtained %zd stack frames.\n", size);

    for (i = 0; i < size; i++)
        printf ("%s\n", strings[i]);
    free (strings);
}

void fpe_handler()
{
    printf("floating point error\n");
    print_trace();
    exit(1);
}

void divby0()
{
    int i = 1;
    i = 10/--i;
}

void test()
{
    divby0();
}

int main(int argc, const char *argv[])
{
    int i = 10;
    signal(SIGFPE, fpe_handler);
    test();
    return 0;
}
