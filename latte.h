#ifndef LATTE_H
#define LATTE_H

#include <string>
#include <vector>

#include "caffe/caffe.hpp"
#include "caffe/util/io.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace caffe;
using namespace cv;
using namespace std;

class Latte
{
public:
    Latte(bool useGPU, string modelFilename, string weightsFilename);
    vector<float> getScores(Mat frame);
    pair<float, int> getMaxScoreAndLabel(Mat frame);
    vector<pair<float, int> > getScoresAndLabels(Mat frame, vector<Rect> windows);

private:
    Net<float> *caffe_net;
};

#endif // LATTE_H
