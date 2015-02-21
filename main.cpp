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
    string videoName = "data/DPEigenbackgroundBGS.avi";
    VideoCapture cap(videoName); // open the default camera
    if (!cap.isOpened()) {
        std::cout << "video not opened\n";
        exit(1);
    }

//    string originalVideoName = "data/train.avi";
//    VideoCapture origCap(originalVideoName);
//    if (!origCap.isOpened()) {
//        std::cout << "original video not opened\n";
//        exit(1);
//    }

    Mat frame;
    Mat origFrame;
    ObjectExtractor extractor;
    while(1) {
        cap >> frame;
//        origCap >> origFrame;
        if (!frame.data) {
            break;
        }

        cvtColor(frame,frame,CV_RGB2GRAY);

        vector<Rect> boxes = extractor.extractBoxes(frame);
        for (Rect box : boxes){
            std::cout << box << endl;
            rectangle(frame, box, Scalar(255, 255, 255));
//            rectangle(origFrame, box, Scalar(255, 255, 255));
        }
        imshow("BGS Detection", frame);
//        imshow("Original Detection", origFrame);

        if (cvWaitKey(1) >= 0)
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

