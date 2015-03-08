//
//  bgs_convert.h
//  OpenCVTutorial2
//
//  Created by Chung Yu Wang on 2/10/15.
//  Copyright (c) 2015 Jacky Wang. All rights reserved.
//

#ifndef __OpenCVTutorial2__bgs_convert__
#define __OpenCVTutorial2__bgs_convert__

#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "package_bgs/FrameDifferenceBGS.h"
#include "package_bgs/WeightedMovingMeanBGS.h"
#include "package_bgs/WeightedMovingVarianceBGS.h"
#include "package_bgs/AdaptiveBackgroundLearning.h"
#include "package_bgs/AdaptiveSelectiveBackgroundLearning.h"
#include "package_bgs/dp/DPEigenbackgroundBGS.h"
#include "package_bgs/dp/DPZivkovicAGMMBGS.h"

using namespace cv;

class BGSConvertor {
private:
    string bgs_class;
    IBGS *bgs;
public:
    BGSConvertor(std::string bgs_class);
    ~BGSConvertor();
    
    VideoCapture convert_video(VideoCapture capture, std::string store_path);
    Mat convert_image(Mat frame, Mat img_bkgmodel, std::string store_path);
};

#endif /* defined(__OpenCVTutorial2__bgs_convert__) */
