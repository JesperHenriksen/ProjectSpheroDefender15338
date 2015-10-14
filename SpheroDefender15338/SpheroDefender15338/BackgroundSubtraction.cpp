#include "BackgroundSubtraction.h"
#include <queue>

using namespace cv;
using namespace std;

queue<Mat> model;
queue<Mat> stash;
Mat collectedBackground;
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
    
    frame.convertTo(grayFrame, CV_16UC1);
    //add(grayFrame, model, model);
    model.push(grayFrame);
    for (int i = 0; i < model.size(); i++) {
        add(model.front(), collectedBackground, collectedBackground);
        stash.push(model.front());
        model.pop();
    }
    model = stash;

    createMask();
        
    if (model.size() >= frameLimit) {
        model.pop();
    }
}

void BackgroundSubtraction::createMask() {
    convertScaleAbs(collectedBackground, mask, 1.0 / model.size());
    mask.convertTo(mask, CV_8UC1);
}

Mat BackgroundSubtraction::subtractBackground(Mat frame) {
    Mat result;
    if (model.size() >= frameLimit) {
        subtract(frame, mask, result);
    }
    else {
        averageBackground(frame);
    }
    return result;
}