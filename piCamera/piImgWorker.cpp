#include <piImgWorker.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <opencv2/highgui.hpp>

//using namespace cv;
//using namespace std;

piImgWorker::piImgWorker(int _color_black, bool _do_morphological ){
	colorBlack = _color_black;
	doMorphological = _do_morphological; 

}

void piImgWorker::Morphological(cv::Mat &_img){
	// morphological opening (removes small objects from the foreground)
	cv::erode(_img, _img, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10)));
	cv::dilate(_img, _img, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10)));
	// morphological closing (removes small holes from the foreground), two iteration
	cv::dilate(_img, _img, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10)), cv::Point(-1, -1), 2); 
	cv::erode(_img, _img, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10)), cv::Point(-1, -1), 2);
}


void piImgWorker::imgConvert(cv::Mat &_img){
	cv::cvtColor(_img, _img, cv::COLOR_BGR2GRAY);  
	//cv::cvtColor(frmSrc, _img, cv::COLOR_BGR2HLS);  //cv::COLOR_BGR2HSV  
	//cv::GaussianBlur(_img, _img, cv::Size(7, 7), 0, 0);
	cv::threshold(_img, img, colorBlack, 255, cv::THRESH_BINARY);
}

bool piImgWorker::Do(cv::Mat _img){

	imgConvert(_img);	
	if (doMorphological) Morphological(img);
	if(!getPoints(img)) return false;

	degDeviationFromCenter = getDegDeviationFromCenter();
	degRelativeDeviation = getDegRelativeDeviation();
}

int piImgWorker::getDegRelativeDeviation(){
	int a = (pntBottomLeft.x + pntBottomRight.x) / 2 - (pntTopRight.x + pntTopLeft.x) / 2  ;
	int b = pntTopRight.y - pntBottomRight.y;
	if(b == 0) b = 1;
	return atan((double)a/b) * 180 / PI;
}

int piImgWorker::getDegDeviationFromCenter(){
	int a = (pntTopRight.x + pntTopLeft.x) / 2 - 640 / 2;
	int b = pntBottomRight.y;
	if(b == 0) b = 1;

	return atan((double)a/b) * 180 / PI;
}

bool piImgWorker::getPoints(cv::Mat &_img){
	bool b = false;

	for(int i = 0; i < _img.rows; i++){
		for(int j = 0; j < _img.cols; j++){
			if(_img.at<char>(i, j) <= colorBlack) {
				pntBottomLeft = cv::Point(j, i);
				b = true;
				break;
			}		
		}
		if(b != true) continue; 
		for(int j = _img.cols - 1; j >= 0; j--){
			if(_img.at<char>(i, j) <= colorBlack) {
				pntBottomRight = cv::Point(j, i);
				break;
			}		
		}
	}
	if(b != true) return false; // there is not any black point

	// TBD
	b = false;
	for(int i = _img.rows; i >= 0; i--){
		for(int j = 0; j < _img.cols; j++){
			if(_img.at<char>(i, j) <= colorBlack) {
				pntTopLeft = cv::Point(j, i);
				b = true;
				break;
			}		
		}
		if (b != true) continue;
		for(int j = _img.cols - 1; j >= 0; j--){
			if(_img.at<char>(i, j) <= colorBlack) {
				pntTopRight = cv::Point(j, i);
				break;
			}		
		}
	}

	return true;
}
