#include <stdio.h>
#include <math.h>
typedef struct _point
{
    double x,y;
} point;

double distance(point p1, point p2) {
    return sqrt(pow(p1.x-p2.x, 2) + pow(p1.y - p2.y, 2));
}

void kclass(point ps[], int N, int k, int labels[])
{
    point centers[k];
    int i, j;
    for(i = 0; i < k; ++i) {
        centers[i] = ps[i];
        labels[i] = i;
    }

    double mindist = distance(centers[0], centers[1]);
    int c1 = 0, c2 = 1;
    for(i = 0; i < k - 1; ++i) {
        for(j = i+1; j < k; ++j) {
            double newdist = distance(centers[i], centers[j]);
            if(newdist < mindist) {
                mindist = newdist;
                c1 = i;
                c2 = j;
            }
        }
    }
    printf("c1 = %d, c2 = %d\nmin c2c dist = %f\n", c1, c2, mindist);

    for(i = k; i < N; ++i) {
        double mindist2 = distance(ps[i], centers[0]);
        labels[i] = 0;
        for(j = 0; j < k; ++j) {
            double newdist2 = distance(ps[i], centers[j]);
            if(newdist2 < mindist2) {
                mindist2 = newdist2;
                labels[i] = j;
            }
        }
        printf("labels[%d] = %d min p2c dist = %f\n", i, labels[i], mindist2);
        // shortest distance between 2 clusters is shorter than the individual point
        if(mindist < mindist2) {
            printf("labels[%d] is individual\n", i);
            // 1. c1 = c1+c2, c2={}
            // 2. c2 = {ps[i]}
            // 3. update centers[c1], centers[c2]
            // 4. update c1, c2
            for(j = 0; j < i; ++j) {
                if(labels[j] == c2) {
                    labels[j] = c1;
                }
            }

            labels[i] = c2;

            centers[c2] = ps[i];
            point center1 = {0, 0};
            int count1 = 0;
            for(j = 0; j < i; ++j) {
                if(labels[j] == c1) {
                    ++count1;
                    center1.x += ps[j].x;
                    center1.y += ps[j].y;
                }
            }
            if(count1 != 0) {
                centers[c1].x = center1.x/count1;
                centers[c1].y = center1.y/count1;
            }

            // update c1,c2
            int ii,jj;
            c1 = 0;
            c2 = 1;
            mindist = distance(centers[0], centers[1]);
            printf("update c1 c2\n");
            for(ii = 0; ii < k - 1; ++ii) {
                for(jj = ii+1; jj < k; ++jj) {
                    double newdist = distance(centers[ii], centers[jj]);
                    printf("new-c2c-dist[%d, %d] = %f\n", ii, jj, newdist);
                    if(newdist < mindist) {
                        mindist = newdist;
                        c1 = ii;
                        c2 = jj;
                    }
                }
            }
            printf("c1 = %d, c2 = %d\nmin c2c dist = %f\n", c1, c2, mindist);
        }
    }
}

int main(int argc, const char *argv[])
{
    point ps[] = {
        {1,1},
        {1,2},
        {2,1},
        {2,2},

        {1, 100},
        {1, 101},
        {2, 100},
        {2, 101},

        {100, 1},
        {100, 2},
        {101, 1},
        {101, 2},

        {100, 100},
        {100, 101},
        {101, 100},
        {101, 101}
    };
    int N = sizeof(ps)/sizeof(point);
    int labels[N];
    kclass(ps, N, 4, labels);
    
    int i;
    for(i = 0; i < N; ++i) {
        printf("labels[%d] = %d\n", i, labels[i]);
    }
    return 0;
}
