#ifndef NONMAXSUPPRESSION_H
#define NONMAXSUPPRESSION_H

#include <vector>
#include <utility>
#include <tuple>
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

class NonMaxSuppression
{
public:
    NonMaxSuppression();
    vector<tuple<Rect, float, int>> suppress(vector<Rect> windows, vector<pair<float, int>> scoreLabels);
};

#endif // NONMAXSUPPRESSION_H
