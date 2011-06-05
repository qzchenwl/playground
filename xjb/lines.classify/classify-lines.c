#include <stdio.h>

typedef struct _point {
    int x, y;
} point;

typedef struct _line {
    point p[2];
} line;

double getk(line l1, line l2) {
    return (l2.p[1] - l1.p[1]) / (l2.p[0] - l1.p[0]);
}

double getd(line l1, line l2) {
    return l1.p[1] - l1.p[0]*getk(l1, l2);
}

double delta(line l1, line l2) {
    return getk(l1, l2) * getk(l1, l2) + getd(l1, l2) * getd(l1, l2);
}

int main(int argc, const char *argv[])
{
    return 0;
}
