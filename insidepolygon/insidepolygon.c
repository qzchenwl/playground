#include <stdio.h>
#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)
#define INSIDE 0
#define OUTSIDE 1

typedef struct {
    int x, y;
} point;

int insidePolygon(point *polygon, int n, point p)
{
    int counter = 0;
    int i;
    double xinters;
    point p1,p2;

    p1 = polygon[0];
    for(i = 1; i <= n; ++i) {
        p2 = polygon[i % n];
        if(p.y >  MIN(p1.y, p2.y) && \
           p.y <= MAX(p1.y, p2.y) && \
           p.x <= MAX(p1.x, p2.x) && \
           p1.y != p2.y) {
            xinters = (p.y - p1.y)*(p2.x - p1.x)/(p2.y - p1.y) + p1.x;
            if(p1.x == p2.x || p.x <= xinters)
                ++counter;
        }
        p1 = p2;
    }

    if(counter % 2 == 0)
        return (OUTSIDE);
    else
        return (INSIDE);
}

int main(int argc, const char *argv[])
{
    point polygon[4] = {
        {200,200},
        {270,150},
        {320,220},
        {250,400}                     
    };
    point p = {260,390};
    int i = insidePolygon(polygon, 4, p);
    printf("%d\n", i);
    return 0;
}
