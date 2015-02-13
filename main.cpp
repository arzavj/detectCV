#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <thread>
#include <iostream>
#include <fstream>
#include "ObjectExtractor.h"

using namespace cv;
using namespace std;

int main(int, char **)
{
    Mat frame = imread("data/testframe_3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if ( frame.rows <= 0 || frame.cols <= 0 ) {
        printf("Fail to load image\n");
        return 1;
    }

    ObjectExtractor extractor;
    vector<Rect> boxes = extractor.extractBoxes(frame);
    for (Rect box : boxes){
        cout << box << endl;
        rectangle(frame, box, Scalar(255, 255, 255));
    }
    namedWindow("still image", CV_WINDOW_AUTOSIZE);
    imshow("still image", frame);
    waitKey(0);
    return 0;
}
