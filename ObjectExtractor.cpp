#include "ObjectExtractor.h"
#include <math.h>

struct box{
    int minY, maxY, minX, maxX;
};

ObjectExtractor::ObjectExtractor()
{

}

vector<Rect> ObjectExtractor::extractBoxes(Mat frame){

    return cluster(frame);
}


vector<Rect> ObjectExtractor::cluster(Mat frame){
    // First allocate a vector of all the active points
    vector<Vec2i> whitePoints;
    for (int y = 0; y < frame.rows; y++){
        for (int x = 0; x < frame.cols; x++){
            uchar pxVal = frame.at<uchar>(y, x);
            if (pxVal > 200) {
                Vec2i pt(x, y);
                whitePoints.push_back(pt);
            }
        }
    }

    // Construct a Mat with all the points
    Mat samples(whitePoints.size(), 2, CV_32F);
    for (int i = 0; i < whitePoints.size(); i++){
        //samples.at<Vec2b>(i) = whitePoints[i];
        int x = whitePoints[i][0];
        samples.at<float>(i, 0) = whitePoints[i][0];
        samples.at<float>(i, 1) = whitePoints[i][1];
    }

    // Perform k-means
    int clusterCount = 6;
    Mat clusterAssignments;
    int attempts = 2;
    Mat centers;
    double error = kmeans(samples, clusterCount, clusterAssignments, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);

    /*
    double prevError = 0;
    for (clusterCount = 1; clusterCount < 10; clusterCount++){ //sketchy, using MLPack later
        Mat newClusterAssignments;
        double error = kmeans(samples, clusterCount, newClusterAssignments, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);
        error = sqrt(error / whitePoints.size());
        cout << clusterCount << "    " << error << "      " << prevError / error << endl;
        if (prevError / error != 0.0 && prevError / error < 2.0) break;
        prevError = error;
        clusterAssignments = newClusterAssignments;
    }*/

    vector<box> boxes(clusterCount);
    for (int i = 0; i < clusterCount; i++){
        boxes[i].minY = frame.rows;
        boxes[i].maxY = 0;
        boxes[i].minX = frame.cols;
        boxes[i].maxX = 0;
    }
    for (int i = 0; i < whitePoints.size(); i++){
        int clusterId = clusterAssignments.at<int>(i, 0);
        Vec2i pt = whitePoints[i];
        int x = pt[0];
        int y = pt[1];
        if (y < boxes[clusterId].minY) boxes[clusterId].minY = y;
        if (x < boxes[clusterId].minX) boxes[clusterId].minX = x;
        if (y > boxes[clusterId].maxY) boxes[clusterId].maxY = y;
        if (x > boxes[clusterId].maxX) boxes[clusterId].maxX = x;
    }

    vector<Rect> rects;
    for (box b : boxes){
        Point2i minPt(b.minX, b.minY);
        Point2i maxPt(b.maxX, b.maxY);
        rects.push_back(Rect(minPt, maxPt));
    }
    return rects;
}
