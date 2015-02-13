#ifndef OBJECTEXTRACTOR_H
#define OBJECTEXTRACTOR_H
#pragma once

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class ObjectExtractor
{
public:
    ObjectExtractor();
    vector<Rect> extractBoxes(Mat frame);
private:
    vector<Rect> cluster(Mat frame);
};

#endif // OBJECTEXTRACTOR_H
