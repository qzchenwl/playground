#include <stdio.h>

#define N 15
#define swap(a, b) {int c = a; a = b; b = c;}

void bubblesort(int *array, int n)
{
    int i, j;
    for (i = n; i >= 1; --i) {
        for (j = 0; j < i - 1; ++j)
            if (array[j] > array[j+1])
                swap(array[j], array[j+1]);
    }
}

int main(int argc, const char *argv[])
{
    int array[N];
    int i;
    srand(time(NULL));
    for(i = 0; i < N; ++i) {
        array[i] = random() % N;
        printf("%4d", array[i]);
    }
    printf("\n");
    bubblesort(array, N);
    for(i = 0; i < N; ++i)
        printf("%4d", array[i]);
    printf("\n");

    return 0;
}
