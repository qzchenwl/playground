#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define N 15
#define swap(a, b) {int c = a; a = b; b = c;}

int partition(int *array, int left, int right, int pivotidx)
{
    int i, pivot, storeidx;
    pivot = array[pivotidx];
    swap(array[pivotidx], array[right]);
    storeidx = left;
    for(i = left; i <= right - 1; ++i) {
        if(array[i] <= pivot) {
            swap(array[i], array[storeidx]);
            ++storeidx;
        }
    }
    swap(array[storeidx], array[right]);
    return storeidx;
}

void quicksort(int *array, int left, int right)
{
    if (right > left) {
        int pivotidx = left + random() % (right - left);
        int newpivotidx = partition(array, left, right, pivotidx);
        quicksort(array, left, newpivotidx - 1);
        quicksort(array, newpivotidx + 1, right);
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
    quicksort(array, 0, N-1);
    for(i = 0; i < N; ++i)
        printf("%4d", array[i]);
    printf("\n");
    return 0;
}
