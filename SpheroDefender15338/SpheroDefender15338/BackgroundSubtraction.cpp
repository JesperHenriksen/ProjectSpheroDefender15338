#include "BackgroundSubtraction.h"

using namespace cv;
using namespace std;

vector<Mat> model; //Mat for storing the frame captured by the camera
Mat collectedBackground; //Collects the model Mat
//Mat clearBackground; //Assigned to collectedBackground to avoid getting a total black picture
Mat mask; //Mat for holding the mask
int frameLimit = 300; //Maximum number frames allowed to be stored


BackgroundSubtraction::BackgroundSubtraction()
{
}

BackgroundSubtraction::~BackgroundSubtraction()
{
}

//Function for getting the background
Mat BackgroundSubtraction::subtractBackground(Mat frame) {
    if (model.size() >= frameLimit) { //if the model's size is bigger or equal to the frame limit
        subtract(frame, mask, frame); //subtract the mask from the frame and output it into the frame
    }
    else {
        averageBackground(frame); //Calls the function averageBackground
    }
    return frame; //Returns the value of frame
}

//Function for getting the average background
void BackgroundSubtraction::averageBackground(Mat frame) {
    Mat grayFrame;
    //frame.copyTo(grayFrame);
    frame.convertTo(grayFrame, CV_8UC1); //Apply 8 bit to grayFrame
    frame.convertTo(grayFrame, CV_16UC1); //Apply 16 bit to grayFrame to avoid clipping

    model.push_back(grayFrame); //Push grayFrame to the back of model

    //Loop through the size of model and add the position of the model at i and the collectedBackground to the collectedBackground
    for (int i = 1; i < model.size(); i++) {
        add(model.at(i), collectedBackground, collectedBackground);
    }

    createMask(); //Call function for creating the mask
    
    //Checking if the size of model is bigger than the frame limit and if so the element in the beggining of model is erased
    if (model.size() >= frameLimit) {
        model.erase(model.begin());
    }
}

//Function for making a mask
void BackgroundSubtraction::createMask() {
    convertScaleAbs(collectedBackground, mask, 1.0 / model.size()); //Calculates the absolute values taking in collectedBackground, outputting mask and using the scale factor 1.0 divided with the size of the model
    mask.convertTo(mask, CV_8UC1); //Converts the mask to 8 bit
}