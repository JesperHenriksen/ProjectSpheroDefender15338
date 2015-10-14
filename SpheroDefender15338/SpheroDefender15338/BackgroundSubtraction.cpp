#include "BackgroundSubtraction.h"

using namespace cv;
//Mat model = Mat(640, 480, CV_);
BackgroundSubtraction::BackgroundSubtraction()
{
}

BackgroundSubtraction::~BackgroundSubtraction()
{
}
//
void createMask(Mat frame) {
    Mat grayFrame;
    frame.convertTo(grayFrame, CV_8UC1);
    //add(grayFrame, model, model);
}