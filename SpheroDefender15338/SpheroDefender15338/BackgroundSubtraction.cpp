#include "BackgroundSubtraction.h"
#include <queue>
#include <list>
#include <algorithm>

using namespace cv;
using namespace std;

vector<Mat> model;
//vector<Mat> stash;
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
    frame.convertTo(grayFrame, CV_8UC1);
    frame.convertTo(grayFrame, CV_16UC1);
    //add(grayFrame, model, model);
    model.push_back(grayFrame);
    list<Mat>::iterator it;
    for (int i = 1; i < model.size(); i++) {
        collectedBackground += model.at(i);
        //it = find(model.begin(), model.end(), model.);
        //advance(it, 1);
        //add(it, collectedBackground, collectedBackground);
        //add(model.front(), collectedBackground, collectedBackground);
        //stash.push(model.front());
        //model.pop_front();
    }
    //model = stash;

    createMask();
        
    if (model.size() >= frameLimit) {
        model.erase(model.begin());
    }
}

void BackgroundSubtraction::createMask() {
    convertScaleAbs(collectedBackground, mask, 1.0 / model.size());
    mask.convertTo(mask, CV_8UC1);
    collectedBackground = clearBackground;
}

Mat BackgroundSubtraction::subtractBackground(Mat frame) {
    
    if (model.size() >= frameLimit) {
        subtract(frame, mask, frame); // frame = frame - mask
    }
    else {
        averageBackground(frame);
    }
    return frame;
}