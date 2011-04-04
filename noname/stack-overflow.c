#include <stdio.h>
#include <signal.h>

void helper()
{
    static int i = 0;
    helper();
}

int main(int argc, const char *argv[])
{
    helper();
    return 0;
}
