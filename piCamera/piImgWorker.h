#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <stdlib.h>
//#include <opencv2/highgui.hpp>

#define PI 3.14

class piImgWorker {
private:
	int colorBlack = 80;
	bool doMorphological = false;
	void Morphological(cv::Mat &_img);
	void imgConvert(cv::Mat &_img);
	bool getPoints(cv::Mat &_img);
	int getDegDeviationFromCenter();
	int getDegRelativeDeviation();
	
public:
	int degDeviationFromCenter;
	int degRelativeDeviation;
	cv::Mat img;
	cv::Point pntTopLeft, pntTopRight, pntBottomLeft, pntBottomRight;
	piImgWorker(int _color_black, bool _do_morphological );
	bool Do(cv::Mat _img);
};
