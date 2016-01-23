#include "opencv2\opencv.hpp"
#include "Minimap.h"
#include "CameraFeed.h"
#include "UserInterface.h"
#include "Battlefield.h"


using namespace cv;
using namespace std;

int main(int, char)
{	

	//webcam variables
	CameraFeed wizardWebcam(1); 
	CameraFeed minimapWebcam(0);
	CameraFeed battlefieldWebcam(0);
	Battlefield battlefield;

	Mat raw, blob, wizardBackground = wizardWebcam.getImageFromWebcam();
    Mat foreground;
	//arrow variables
	Mat arrowInput, arrowThreshold, arrowGrayscale;
	Minimap minimap;
	double spheroX = 0.0, spheroY = 0.0; 
	double minimapXCoord = 0, minimapYCoord = 0;

	//angle
	double angle = 0;
	Mat angleInput, angleThresholded, angleGrayscale;


	//hand tracking variables
	bool isImageGood = false;
	char userInput;
	Mat handInput, handColorThreshold, handGscale, handThreshold, handBackground = wizardWebcam.getImageFromWebcam();

	
	Mat grassfire, fixedGrassfire;
	int handsign = 0;
	
	int kernelSize = 15;
	Mat kernel;
	Mat sat, hue, intensity;
	
	//battlefield variables
	Mat battlefieldInput, spheroTracking, battlefieldReset, battlefieldProjected;
	battlefieldInput = imread("../../../../../Google Drev/MTA15338/Project/Design/ProgramLayers/BattlefieldSmall.png", 1);
	battlefieldReset = imread("../../../../../Google Drev/MTA15338/Project/Design/ProgramLayers/BattlefieldSmall.png", 1);
	Mat battlefieldProjectedReset = imread("../../../../../Google Drev/MTA15338/Project/Design/ProgramLayers/BattlefieldMedium.png", 1);
	battlefieldProjected = imread("../../../../../Google Drev/MTA15338/Project/Design/ProgramLayers/BattlefieldMedium.png", 1);

	//imshow("handBackground", handBackground);
	//while (!isImageGood){
	//	cout << "Is this background image good? (y/n)";
	//	cin >> userInput;
	//	if (userInput == 'y')
	//		isImageGood = true;
	//	else
	//		handBackground = wizardWebcam.getImageFromWebcam();
	//	imshow("handBackground", handBackground);

	//};
	int test = 2; // 1 for arrow and 2 for hand
	for (;;){
		if (test == 1) {
			// get coordinates for arrow
			//get the angle of arrow
			angleInput = minimapWebcam.getImageFromWebcam();
			angleInput *= 1.5; // 1.5 * all pixel values. Makes image brighter
			medianBlur(angleInput, angleInput, 5); 
			minimapWebcam.thresholdImageColor(angleInput, angleInput, 80, 255, 255, 100, 255, 255, 100, 255, 255);  //Params: input,output, minRed,maxRed,newRed,minGreen,maxGreen,newGreen,minBlue,maxBlue,newBlue
			minimapWebcam.thresholdImageColor(angleInput, angleInput, 0, 80, 0, 0, 100, 0, 0, 100, 0); //Params: input,output, minRed,maxRed,newRed,minGreen,maxGreen,newGreen,minBlue,maxBlue,newBlue
			angleGrayscale = minimapWebcam.convertRGBtoGS(angleInput); //convert to grayscale
			angleGrayscale = angleGrayscale * 1.5; //1.5 * all pixel values. Makes image brighter
			medianBlur(angleGrayscale, angleGrayscale, 7); 
			angleGrayscale *= 2; //2 * all pixel values. Makes image brighter
			angleGrayscale.copyTo(angleThresholded); //copies image to new Mat variable
			minimapWebcam.thresholdImage(angleThresholded, angleThresholded, 150, 256, 200, 60, 150, 100, 0, 60, 0); //Params: input,output,firstMin,firstMax,firstNew,secondMin,secondMax,secondNew,thirdMin,thirdMax,thirdNew
			angle = minimap.getAngleOfArrow(angleThresholded, 0, 100); //see minimap
			angleThresholded.copyTo(arrowThreshold);
			minimapWebcam.thresholdImage(arrowThreshold, arrowThreshold, 0, 150, 255);
			minimapWebcam.thresholdImage(arrowThreshold, arrowThreshold, 190, 210, 0);
			minimap.placeSpell(arrowThreshold, 250, 256, minimapXCoord, minimapYCoord);

			//imshow("raw", angleInput);
			//imshow("angle threshold arrow", angleThresholded);
			imshow("threshold arrow position", arrowThreshold);

			cout << angle << " " << minimapXCoord << ", " << minimapYCoord << "\n";
		} 
		else
		{
			//threshold hand
			handInput = wizardWebcam.getImageFromWebcam();
			//Mat handSubtracted;
			//handSubtracted = Mat::zeros(handInput.rows, handInput.cols, );
			//wizardWebcam.subtractImage(handInput, handBackground, handSubtracted);
			cvtColor(handInput, sat, COLOR_BGR2HSV); //converts handInput to HSV and saves in sat. See bottom of CameraFeed
			sat.copyTo(handColorThreshold);
			blur(handColorThreshold, handColorThreshold, Size(7,7)); //mean blur
			wizardWebcam.thresholdHand(sat, handColorThreshold, 35, 80, 255); // threshold HSV image. 35-80 is green
			cvtColor(handColorThreshold, handColorThreshold, CV_BGR2GRAY); // (R + G + B) / 3
			medianBlur(handColorThreshold, handColorThreshold, 9);
			kernel.ones(kernelSize, kernelSize, CV_8UC1); //Mat.ones makes a matrix with ones in all entries. Mat.ones(sizeX, sizeY, 8 bit unsigned one channel);

			//closing
			dilate(handColorThreshold, handColorThreshold, kernel);
			medianBlur(handColorThreshold, handColorThreshold, 9);
			erode(handColorThreshold, handColorThreshold, kernel);
			//opening
			erode(handColorThreshold, handColorThreshold, kernel);
			dilate(handColorThreshold, handColorThreshold, kernel);
		
			grassfire = Mat::zeros(handColorThreshold.rows, handColorThreshold.cols, handColorThreshold.type()); //Mat::zeros makes zeros in all entries.
			wizardWebcam.grassFire(handColorThreshold, grassfire);  // see grassfire line 67
			handColorThreshold.copyTo(fixedGrassfire); 
			wizardWebcam.thresholdGrassfireID(grassfire,fixedGrassfire);
			medianBlur(fixedGrassfire, fixedGrassfire, 13);

			//imshow("grassfire", grassfire);
			imshow("threshold", handColorThreshold);
			imshow("fixed grassfire", fixedGrassfire);
			imshow("input", handInput);
			
			//recognize hand
			handsign = wizardWebcam.chooseHandsign(fixedGrassfire);
			//cout << "handsign = " << handsign << "\n";
			switch (handsign){
			case 1: 
				cout << "Stone \n";
				break;
			case 2:
				cout << "Wall\n";
				break;
			case 3:
				cout << "Boomerang\n";
				break;
			case 4:
				cout << "Sentry\n";
				break;
			default:
				cout << "No handsign found\n";
				break;
			}
		}
		//spheroTracking = battlefieldWebcam.getImageFromWebcam();
		//imshow("battlefield", spheroTracking);
		//battlefield.trackSphero(battlefieldWebcam,spheroX,spheroY);
		//cout << spheroX  << ", " << spheroY << "\n";
		//bool bob = battlefield.isSpheroOutOfBounds(battlefieldInput, spheroX, spheroY);
		//cout << bob << "\n";
		//if (handsign != 0){
		//	battlefield.throwSpell(battlefieldInput, minimapXCoord, minimapYCoord, handsign, 1);
		//	battlefield.throwSpell(battlefieldProjected, minimapXCoord, minimapYCoord, handsign, 2);
		//}
		//battlefield.removeObstacle(battlefieldInput, battlefieldReset, spheroX, spheroY, 1);
		//battlefield.removeObstacle(battlefieldProjected, battlefieldProjectedReset, spheroX, spheroY, 2);
		//imshow("battlefield YARGH", battlefieldInput);
		//imshow("battlefield projection yes", battlefieldProjected);

		//end of code
		if (waitKey(30) >= 0)
			break;
	}
	waitKey(0);
	return 0;
}