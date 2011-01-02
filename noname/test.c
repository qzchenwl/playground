#include <stdio.h>
#include <math.h>
int main(int argc, const char *argv[])
{
    int i;
    for (i = 0; i < 80; i++) {
        printf("%f ",(sin(i/10.0)*10));
    }
    return 0;
}
