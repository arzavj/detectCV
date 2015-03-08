#include "ObjectExtractor.h"
#include <math.h>
#include <unordered_set>

#define SW_H 200
#define SW_W 120
#define SW_A SW_H*SW_W
#define THRESH 0.1
#define THRESH_NUMPX (int)(THRESH*SW_A)
#define DX 30
#define DY 10
#define BOUNDING_BOX_AREA_THRESH 500

struct box{
    int minY, maxY, minX, maxX;
};

ObjectExtractor::ObjectExtractor()
{

}

struct Point2iHash {
   size_t operator() (const Point2i &p) const {
     return p.x+7919*p.y;
   }
};

static void unordered_set_intersect(unordered_set<Point2i, Point2iHash> &out,
    const unordered_set<Point2i, Point2iHash> &in1, const unordered_set<Point2i, Point2iHash> &in2)
{
    if (in2.size() < in1.size()) {
        unordered_set_intersect(out, in2, in1);
        return;
    }
    for (unordered_set<Point2i, Point2iHash>::const_iterator it = in1.begin(); it != in1.end(); it++)
    {
        if (in2.find(*it) != in2.end())
            out.insert(*it);
    }
}

static bool hasSufficientWhitePixels(Point2i& topLeft, unordered_set<Point2i, Point2iHash>* rowWhites,
                                     int numRows, unordered_set<Point2i, Point2iHash>* colWhites,
                                     int numCols){
    int lastWindowCol = topLeft.x+SW_W;
    int lastWindowRow = topLeft.y+SW_H;
    if (topLeft.x < 0 || topLeft.y < 0 || lastWindowCol >= numCols || lastWindowRow >= numRows) {
        return false;
    }

    unordered_set<Point2i, Point2iHash> colPixels;
    unordered_set<Point2i, Point2iHash> whitePixels;
    for (int col = topLeft.x; col < lastWindowCol; col++){
        colPixels.insert(colWhites[col].begin(), colWhites[col].end());
    }
    for (int row = topLeft.y; row < lastWindowRow; row++){
        unordered_set_intersect(whitePixels, rowWhites[row], colPixels);
    }

    return whitePixels.size() > THRESH_NUMPX;

}

static vector<Rect> extractBoxesSlow(Mat frame) {
    unordered_set<Point2i, Point2iHash>* rowWhites = new unordered_set<Point2i, Point2iHash>[frame.rows];
    unordered_set<Point2i, Point2iHash>* colWhites = new unordered_set<Point2i, Point2iHash>[frame.cols];
    vector<int>* rowWhiteVectors  = new vector<int>[frame.rows];
    for (int y = 0; y < frame.rows; y++){
        for (int x = 0; x < frame.cols; x++){
            uchar pxVal = frame.at<uchar>(y, x);

            if (pxVal > 200) {
                Point2i pt(x, y);
                rowWhites[y].insert(pt);
                colWhites[x].insert(pt);
                rowWhiteVectors[y].push_back(x);
            }
        }
    }

    vector<Rect> rects;
    for (int y = 0; y < frame.rows; y += DY){
        for (int i = 0; i < rowWhiteVectors[y].size(); i += DY) {
            Point2i top(rowWhiteVectors[y][i], y);
            for (int dx = 0; dx < SW_W; dx += DX) {
                Point2i topLeft(top.x - dx, top.y);
                if (hasSufficientWhitePixels(topLeft, rowWhites, frame.rows, colWhites, frame.cols)){
                    Point2i bottomRight(topLeft.x + SW_W, topLeft.y + SW_H);
                    rects.push_back(Rect(topLeft, bottomRight));
                }
            }
        }
    }

    delete [] rowWhites;
    delete [] colWhites;
    delete [] rowWhiteVectors;

    return rects;
}

static void getSlidingWindows(Rect boundingBox, vector<Rect>& slidingWindows, Size frameSize) {
    Point topLeft = boundingBox.tl();
    Point bottomRight = boundingBox.br();
    int y = topLeft.y;
    do {
        int x = topLeft.x;
        do {
            if ((x + SW_W) < frameSize.width && (y + SW_H) < frameSize.height) {
                slidingWindows.push_back(Rect(x, y, SW_W, SW_H));
            }
            x += DX;
        } while(x <= (bottomRight.x - SW_W));
        y += DY;
    } while(y <= (bottomRight.y - SW_H));
}

static vector<Rect> extractContourBoxes(Mat frame) {
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    Mat blur_out;
    GaussianBlur(frame, blur_out, Size(1,1), 2.0, 2.0);

    blur_out = blur_out >= 200;
    int erosion_size = 1;
    Mat element = getStructuringElement(MORPH_RECT, Size( 2*erosion_size + 1, 2*erosion_size+1 ));

    Mat morphedFrame;
    morphologyEx(blur_out, morphedFrame, MORPH_CLOSE, element);
//    dilate(blur_out, morphedFrame, element, Point(-1, -1), 1);
//    erode(morphedFrame, morphedFrame, element, Point(-1, -1), 2);
//    dilate(morphedFrame, morphedFrame, element, Point(-1, -1), 1);

    findContours(morphedFrame, contours, hierarchy, CV_RETR_EXTERNAL,  CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    // Approximate contours to get bounding rects
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRects( contours.size() );

    for( int i = 0; i < contours.size(); i++ )
    {
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        boundRects[i] = boundingRect( Mat(contours_poly[i]) );
    }

    vector<Rect> slidingWindows;
    for (Rect boundingBox: boundRects) {
//        rectangle(morphedFrame, boundingBox, Scalar(255, 255, 255));
//        Size s = boundingBox.size();
//        char text[21];
//        sprintf(text, "%d x %d", s.width, s.height);
//        putText(morphedFrame, text, boundingBox.tl(), FONT_HERSHEY_SIMPLEX, 0.1, Scalar(255, 255, 255));
        if (boundingBox.area() > BOUNDING_BOX_AREA_THRESH) {
            getSlidingWindows(boundingBox, slidingWindows, frame.size());
        }
    }

    return slidingWindows;
}

vector<Rect> ObjectExtractor::extractBoxes(Mat frame) {
    // return extractBoxesSlow(frame);
    return extractContourBoxes(frame);
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

    vector<Rect> rects;
    int clusterCount = 6;
    if (whitePoints.size() < clusterCount) {
        std::cout << "Too few white points to cluster! \n";
        return rects;
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

    for (box b : boxes){
        Point2i minPt(b.minX, b.minY);
        Point2i maxPt(b.maxX, b.maxY);
        rects.push_back(Rect(minPt, maxPt));
    }
    return rects;
}
