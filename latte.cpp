#include "latte.h"

Latte::Latte(bool useGPU, string modelFilename, string weightsFilename)
{
    Caffe::set_mode(Caffe::CPU);
    caffe_net = new Net<float>(modelFilename, TEST);
    caffe_net->CopyTrainedLayersFrom(weightsFilename);
}

float Latte::classify(Mat frame)
{
    Mat resized;
    cout << "Resizing frame to 256x256" << endl;
    resize(frame, resized, Size(227, 227));
    Datum datum;
    CVMatToDatum(resized, &datum);
    vector<Datum> datum_vector;
    datum_vector.push_back(datum);
    boost::dynamic_pointer_cast<MemoryDataLayer<float> >(caffe_net->layers()[0])->AddDatumVector(datum_vector);
    vector<Blob<float>* > bottom_vec;
    float iter_loss;
    const vector<Blob<float>*>& result = caffe_net->Forward(bottom_vec, &iter_loss);
    const float score = result[1]->cpu_data()[0];
    cout << "Score = " << score << endl;
    return score;
}
