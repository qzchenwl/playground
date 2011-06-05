#include <highgui.h>

int main(int argc, const char *argv[])
{
    IplImage *img = cvLoadImage(argv[1], CV_LOAD_IMAGE_ANYCOLOR);
    cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
    cvShowImage("Example1", img);
    cvWaitKey(0);
    cvReleaseImage(&img);
    cvDestroyWindow("Example1");
    return 0;
}
