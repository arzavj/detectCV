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
    string originalVideoName = "data/DPEigenbackgroundBGS.avi";
    VideoCapture inputVideo(originalVideoName);
    if (!inputVideo.isOpened()) {
        std::cout << "input video not opened\n";
        exit(1);
    }

//    IBGS *bgs = new DPEigenbackgroundBGS();
    Mat frame = imread("data/testframe_1.jpg");
    ObjectExtractor extractor;
//    Mat img_mask;
//    Mat img_bkgmodel;
//    Mat imageGrey;

//    while(1) {
//        inputVideo >> frame;
//        if (!frame.data) {
//            break;
//        }

//        bgs->process(frame, img_mask, img_bkgmodel);
//        if (img_mask.data) {
//            // Attempt to fix Mac OS gray scale not able to be written
//            Mat imageArr[] {img_mask, img_mask, img_mask};
//            merge(imageArr, 3, imageGrey);
//        }

        cvtColor(frame,frame,CV_RGB2GRAY);
        vector<Rect> boxes = extractor.extractBoxes(frame);
        for (Rect box : boxes){
            std::cout << box << endl;
            rectangle(frame, box, Scalar(255, 255, 255));
        }
        imshow("BGS Detection", frame);

//        if (cvWaitKey(1) >= 0)
//            break;
//    }
    if (cvWaitKey(0) >= 0)
        return 0;
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

