#include <stdio.h>
#include <math.h>
int main(int argc, const char *argv[])
{
    /* */
    int i,j;
    for (i = 0; i < 60; i++) {
        for (j = 0; j < 160; j++) {
            double delta = sin(j/20.0)*25 - (25-i);
            if(delta <= 0.5 && delta > -0.5)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}
