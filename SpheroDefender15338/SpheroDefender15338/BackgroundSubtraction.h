#include "opencv2/opencv.hpp"
#pragma once
using namespace cv;

class BackgroundSubtraction
{
public:
    BackgroundSubtraction();
    ~BackgroundSubtraction();

    void createMask(Mat frame);
private:

};

