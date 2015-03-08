#include <iostream>
#include <iomanip>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "BGSConvertor.h"
#include "ObjectExtractor.h"
#include "caffe/util/io.hpp"
#include "caffe/caffe.hpp"
#include "caffe/blob.hpp"
#include "latte.h"
#include "nonmaxsuppression.h"

using namespace caffe;
using namespace cv;
using namespace std;

/* Prototypes */
void TestBGSVideoConvertor();

const int MAX_N_CLASSES = 9;
String CLASS_LIST[2][MAX_N_CLASSES] = {{"bike",  "bus", "car", "dog", "motorbike", "others", "pedestrian", "skater", "stroller"}, {"pedestrian", "non-pedestrian"}};
String PROTOTXT_LIST[2] = {"models/multiclass_train_val.prototxt", "models/binary_train_val.prototxt"};
String MODEL_LIST[2] = {"models/9classFinetune100000.caffemodel", "models/binaryFinetune100000.caffemodel"};

int main(int, char **)
{
    bool isMultiClass = true;
    // Mapping from label number to label text
    String *classes;
    Latte caffeModel(false, PROTOTXT_LIST[isMultiClass ? 0 : 1], MODEL_LIST[isMultiClass ? 0 : 1]);
    classes = CLASS_LIST[isMultiClass ? 0 : 1];

    string originalVideoName = "data/bike.mov";


    VideoCapture inputVideo(originalVideoName);
    if (!inputVideo.isOpened()) {
        std::cout << "input video not opened\n";
        exit(1);
    }

    // Create output video with same properties as input
    String video_store_path = "cnnOutput2.avi";
    // Intrinsic properties of input
    double dWidth = inputVideo.get(CV_CAP_PROP_FRAME_WIDTH);
    double dHeight = inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT);
    int fps = inputVideo.get(CV_CAP_PROP_FPS);
    //int ex = static_cast<int>(inputVideo.get(CV_CAP_PROP_FOURCC));
    Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

    VideoWriter outputVideo(video_store_path, CV_FOURCC('m', 'p', '4', 'v'), fps, frameSize, true);
    if(!outputVideo.isOpened()) { // check if we succeeded
        printf("output video not opened\n");
        return NULL;
    }

    IBGS *bgs = new DPEigenbackgroundBGS();
    //IBGS *bgs = new DPZivkovicAGMMBGS();
    Mat frame;
    ObjectExtractor extractor;
    Mat img_mask;
    Mat img_bkgmodel;
    Scalar WHITE(255, 255, 255);
    NonMaxSuppression nms;
    float counts[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    float countTotal = 0;
    while(1) {
        inputVideo >> frame;
        if (!frame.data) {
            break;
        }

        bgs->process(frame, img_mask, img_bkgmodel);
//        imshow("BGS Subtracted Frame", img_mask);
        //imwrite("bgsImage.jpg", img_mask );
        cout << frame.rows << ", " << frame.cols << endl;
        vector<Rect> windows = extractor.extractBoxes(img_mask);
        vector<pair<float, int>> scoreLabels = caffeModel.getScoresAndLabels(frame, windows);
        vector<tuple<Rect, float, int>> boxes = nms.suppress(windows, scoreLabels);
        for (tuple<Rect, float, int> boxTuple : boxes) {
            int label = get<2>(boxTuple);
            Rect& box = get<0>(boxTuple);
            rectangle(frame, box, WHITE);
            putText(frame, classes[label], box.tl(), FONT_HERSHEY_SIMPLEX, 0.5,  Scalar( 0, 0, 255 ));
            counts[label]++;
            countTotal++;
            for (int count_i = 0; count_i < sizeof(counts)/sizeof(counts[0]); count_i++) {
                cout << "label " << count_i << " % = " << counts[count_i] / countTotal << endl;
            }
        }

        imshow("BGS Detection", frame);
        printf("Done drawing %d boxes\n", boxes.size());

        //Mat imageArr[] {img_mask, img_mask, img_mask};
        //merge(imageArr, 3, imageGrey);
        outputVideo.write(frame);

        if (cvWaitKey(10) >= 0)
            break;
    }
    outputVideo.release();
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

