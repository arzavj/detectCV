#include "latte.h"

Latte::Latte(bool useGPU, string modelFilename, string weightsFilename)
{
    Caffe::set_mode(Caffe::CPU);
    caffe_net = new Net<float>(modelFilename, TEST);
    caffe_net->CopyTrainedLayersFrom(weightsFilename);
}

vector<pair<float, int> > Latte::getScoresAndLabels(Mat originalFrame, vector<Rect> windows)
{
    vector<pair<float, int> > scoreLabels(windows.size());
    for (int i = 0; i< windows.size(); i++) {
        scoreLabels[i] = getMaxScoreAndLabel(originalFrame(windows[i]));
    }
    return scoreLabels;
}

pair<float, int> Latte::getMaxScoreAndLabel(Mat frame)
{
    vector<float> scores = getScores(frame);
    float maxScore = 0.0;
    int mostLikelyLabel = -1;
    cout << "Window of size = " << frame.size().width << ", " << frame.size().height << endl;
    for (int label = 0; label < scores.size(); label++) {
        if (scores[label] > maxScore) {
            mostLikelyLabel = label;
            maxScore = scores[label];
        }
    }
    cout << "Label = " << mostLikelyLabel << " Score = " << maxScore << endl;
    return make_pair(maxScore, mostLikelyLabel);
}

vector<float> Latte::getScores(Mat frame)
{
    Mat resized;
    resize(frame, resized, Size(256, 256));
//    cout << "resized_col = " << resized.cols << " resized_row = " << resized.rows << endl;
    Datum datum;
    CVMatToDatum(resized, &datum);
    vector<Datum> datum_vector;
    datum_vector.push_back(datum);
    boost::dynamic_pointer_cast<MemoryDataLayer<float> >(caffe_net->layers()[0])->AddDatumVector(datum_vector);
    vector<Blob<float>* > bottom_vec;
    float iter_loss;
    const vector<Blob<float>*>& result = caffe_net->Forward(bottom_vec, &iter_loss);
    const float* result_vec = result[1]->cpu_data();
    vector<float> scores(result[1]->count());
    for (int k = 0; k < scores.size(); ++k) {
        scores[k] = result_vec[k];
    }
    return scores;
}
