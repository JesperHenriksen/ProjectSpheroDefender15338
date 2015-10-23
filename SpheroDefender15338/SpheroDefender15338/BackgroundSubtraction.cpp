#include "BackgroundSubtraction.h"
#include <queue>
#include <list>

using namespace cv;
using namespace std;

vector<Mat> model;
Mat collectedBackground;
Mat clearBackground;
Mat mask;
int frameLimit = 300; //Maximum number of frames stored in queue


BackgroundSubtraction::BackgroundSubtraction()
{
}

BackgroundSubtraction::~BackgroundSubtraction()
{
}


void BackgroundSubtraction::averageBackground(Mat frame) {
    Mat grayFrame;
    //frame.copyTo(grayFrame);
    frame.convertTo(grayFrame, CV_8UC1);
    frame.convertTo(grayFrame, CV_16UC1);

    model.push_back(grayFrame);

    for (int i = 1; i < model.size(); i++) {
        add(model.at(i), collectedBackground, collectedBackground);
    }

    createMask();
        
    if (model.size() >= frameLimit) {
        model.erase(model.begin());
    }
}

void BackgroundSubtraction::createMask() {
    convertScaleAbs(collectedBackground, mask, 1.0 / model.size());
    mask.convertTo(mask, CV_8UC1);
}

Mat BackgroundSubtraction::subtractBackground(Mat frame) {
    
    if (model.size() >= frameLimit) {
        subtract(frame, mask, frame); 
    }
    else {
        averageBackground(frame);
    }
    return frame;
}