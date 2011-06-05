#include <stdio.h>
#include <strings.h>
#include <time.h>
#include <math.h>

typedef struct _point {
    double x, y;
} point;

double distance(point p1, point p2) {
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

double calc_J(point ps[], point centers[], int labels[], int N)
{
    int i;
    double sum = 0;
    for(i = 0; i < N; ++i) {
        sum += distance(ps[i], centers[labels[i]])*distance(ps[i], centers[labels[i]]);
    }
    return sum;
}

void kmeans(point ps[], int N, int k,  int maxiter, double threshold, int labels[])
{
    int i, j, iter;
    double mindist;
    double J, Jprev;
    point centers[k];

    for(i = 0; i < N; ++i) {
        labels[i] = 0;
    }
    srand(time(0));
    for(i = 0; i < k; ++i) {
        int r = rand()%k;
        centers[i].x = ps[r].x*(rand()%100)/50;
        centers[i].y = ps[r].y*(rand()%100)/50;
    }

    Jprev = calc_J(ps, centers, labels, N);
    iter = 0;
    while(1) {

        printf("-------- iter %d --------\n", iter);
        // print k centers
        printf("centers:\n");
        for(i = 0; i < k; ++i) {
            printf("(%f, %f)\n", centers[i].x, centers[i].y);
        }
        // assign each point to the cluster
        printf("labels:\n");
        for(i = 0; i < N; ++i) {
            labels[i] = 0;
            mindist = distance(ps[i], centers[0]);
            for(j = 1; j < k; ++j) {
                double newdist = distance(ps[i], centers[j]);
                if(newdist < mindist) {
                    // update cluster
                    labels[i] = j;
                    mindist = newdist;
                }
            }
            printf("labels[%d] = %d\n", i, labels[i]);
        }

        // update cluster center
        printf("new centers:\n");
        for(i = 0;i < k; ++i) {
            point center = {0, 0};
            int count = 0;
            for(j = 0; j < N; ++j) {
                if(labels[j] == i) {
                    ++ count;
                    center.x += ps[j].x;
                    center.y += ps[j].y;
                }
            }
            if (count != 0) {
                centers[i].x = center.x/count;
                centers[i].y = center.y/count;
            }
            printf("(%f, %f)\n", centers[i].x, centers[i].y);
        }

        ++ iter;
        J = calc_J(ps, centers, labels, N);
        /*
        if(Jprev - J < threshold)
            break;
            */
        Jprev = J;
        if(iter > maxiter)
            break;
    }
}

int main(int argc, const char *argv[])
{
    point ps[] = {
        {1,2},
        {2,2},
        {3,2},
        {1,5},
        {3,3},

        {1, 100},
        {2, 102},
        {3, 101},
        {4, 99},

        {100, 2},
        {101, 3},
        {104, 2},
        {104, 5}
    };
    int N = sizeof(ps)/sizeof(point);
    int labels[N];
    kmeans(ps, N, 3, 100, 0.00000001, labels);

    int i;
    for(i = 0; i < N; ++i) {
        printf("labels[%d] = %d\n", i, labels[i]);
    }
    return 0;
}
