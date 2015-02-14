//
//  bgs_convert.cpp
//  OpenCVTutorial2
//
//  Created by Chung Yu Wang on 2/10/15.
//  Copyright (c) 2015 Jacky Wang. All rights reserved.
//

#include "BGSConvertor.h"
#include <assert.h>

BGSConvertor::BGSConvertor(std::string bgs_class) {
    assert(bgs_class.length() != 0);
    this->bgs_class = bgs_class;
    if (bgs_class.compare("FrameDifferenceBGS") == 0) {
        bgs = new FrameDifferenceBGS();
        return;
    }
    
    if (bgs_class.compare("WeightedMovingVarianceBGS") == 0) {
        bgs = new WeightedMovingVarianceBGS();
        return;
    }
    
    if (bgs_class.compare("WeightedMovingMeanBGS") == 0) {
        bgs = new WeightedMovingMeanBGS();
        return;
    }
    
    if (bgs_class.compare("AdaptiveBackgroundLearning") == 0) {
        bgs = new AdaptiveBackgroundLearning();
        return;
    }
    
    if (bgs_class.compare("AdaptiveSelectiveBackgroundLearning") == 0) {
        bgs = new AdaptiveSelectiveBackgroundLearning();
        return;
    }
    
    std::cout << "No matching BGS Type specified in bgs_convert constructor\n";
}

BGSConvertor::~BGSConvertor() {
    delete bgs;
}

VideoCapture BGSConvertor::convert_video(VideoCapture capture, std::string store_path) {
    std::cout << bgs_class << " converting video, storing to " << store_path << "\n";
    
    if (!capture.isOpened()) {
        printf("input video not opened\n");
        return NULL;
    }
    
    // Intrinsic properties of input
    double dWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    double dHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    int fps = capture.get(CV_CAP_PROP_FPS);
    Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
    
    // Create output video with same properties as input
    VideoWriter output_cap(store_path, CV_FOURCC('I', 'Y', 'U', 'V'), fps, frameSize, true);
    if(!output_cap.isOpened()) { // check if we succeeded
        printf("output video not opened\n");
        return NULL;
    }
    

    Mat frame;
    Mat imageGrey;
    Mat img_mask;
    Mat img_bkgmodel;
    while (1)
    {
        capture >> frame;
        if (!frame.data) break;
        bgs->process(frame, img_mask, img_bkgmodel);
        if (img_mask.data) {
            // Attempt to fix Mac OS gray scale not able to be written
            Mat imageArr[] {img_mask, img_mask, img_mask};
            merge(imageArr, 3, imageGrey);
            output_cap.write(imageGrey);
        }
        if (cvWaitKey(1) >= 0)
            break;
    }
    
    output_cap.release();

    std::cout << bgs_class << " finished converting bgs video\n";
    return VideoCapture(store_path);
}

Mat BGSConvertor::convert_image(Mat frame, Mat img_bkgmodel, std::string store_path) {
    Mat imageGrey;
    Mat img_mask;
    Mat img_bkgmodel1;
    if (frame.data) {
        bgs->process(frame, img_mask, img_bkgmodel1);
        if (img_mask.data) {
            // Attempt to fix Mac OS gray scale not able to be written
            Mat imageArr[] {img_mask, img_mask, img_mask};
            merge(imageArr, 3, imageGrey);
            imwrite(store_path, img_mask);
        }
    }
    
    return img_mask;
}
