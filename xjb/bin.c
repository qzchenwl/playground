#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <math.h>

IplImage *Igray = 0, *It = 0, *Iat;

int main(int argc, const char *argv[])
{
    if(argc != 7) {
        printf("%s threshold threshold_type adaptive_method block_size offset\n", argv[0]);
        return -1;
    }

    double threshold = (double) atof(argv[1]);
    int threshold_type = atoi(argv[2]) ?
        CV_THRESH_BINARY : CV_THRESH_BINARY_INV;
    int adaptive_method = atoi(argv[3]) ?
        CV_ADAPTIVE_THRESH_MEAN_C : CV_ADAPTIVE_THRESH_GAUSSIAN_C;
    int block_size = atoi(argv[4]);
    double offset = (double) atof(argv[5]);

    if((Igray = cvLoadImage(argv[6], CV_LOAD_IMAGE_GRAYSCALE)) == 0)
        return -1;

    It = cvCreateImage(cvSize(Igray->width, Igray->height), IPL_DEPTH_8U, 1);
    Iat = cvCreateImage(cvSize(Igray->width, Igray->height), IPL_DEPTH_8U, 1);

    cvThreshold(Igray, It, threshold, 255, threshold_type);
    cvAdaptiveThreshold(Igray, Iat, 255, adaptive_method, threshold_type, block_size, offset);

    cvNamedWindow("Raw", 1);
    cvNamedWindow("Threshold", 1);
    cvNamedWindow("Adaptive Threshold", 1);

    cvShowImage("Raw", Igray);
    cvShowImage("Threshold", It);
    cvShowImage("Adaptive Threshold", Iat);

    while(1) {if(cvWaitKey(10)&0x7f == 27)break;};

    return 0;
}
