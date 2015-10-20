#include "opencv2/opencv.hpp"
#pragma once
using namespace cv;

class BackgroundSubtraction
{
public:
    BackgroundSubtraction();
    ~BackgroundSubtraction();

    void averageBackground(Mat frame);
    void createMask();
    Mat subtractBackground(Mat frame);
private:

};

