#include <iostream>
#include <iomanip>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "BGSConvertor.h"
#include "ObjectExtractor.h"

using namespace cv;
using namespace std;

/* Prototypes */
void TestBGSVideoConvertor();

int main(int, char **)
{
    string originalVideoName = "data/train.avi";
    VideoCapture inputVideo(originalVideoName);
    if (!inputVideo.isOpened()) {
        std::cout << "input video not opened\n";
        exit(1);
    }

    IBGS *bgs = new DPEigenbackgroundBGS();
    Mat frame;
    ObjectExtractor extractor;
    Mat img_mask;
    Mat img_bkgmodel;
    Mat imageGrey;

    while(1) {
        inputVideo >> frame;
        if (!frame.data) {
            break;
        }

        bgs->process(frame, img_mask, img_bkgmodel);
        imshow("BGS Subtracted Frame", img_mask);

        vector<Rect> boxes = extractor.extractBoxes(img_mask);
        for (Rect box : boxes){
            rectangle(frame, box, Scalar(255, 255, 255));
        }

        imshow("BGS Detection", frame);
        printf("Done drawing %d boxes\n", boxes.size());

        if (cvWaitKey(10) >= 0)
            break;
    }
    return 0;
}

void TestBGSVideoConvertor() {
    VideoCapture capture("data/train.avi"); // open the default camera
    BGSConvertor *convert = new BGSConvertor("FrameDifferenceBGS");

    // Test video convert
    VideoCapture result = convert->convert_video(capture, "data/test.avi");
    Mat vidTest;
    while(1) {
        result >> vidTest;
        if (!vidTest.data) {
            //std::cout << "no result data\n";
            break;
        }

        imshow("Video Test", vidTest);

        if (cvWaitKey(1) >= 0)
            break;
    }
}

