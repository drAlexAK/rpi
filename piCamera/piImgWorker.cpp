#include <piImgWorker.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <opencv2/highgui.hpp>

//using namespace cv;
//using namespace std;

piImgWorker::piImgWorker(int _black){
	black = _black;

}


bool piImgWorker::getPoint(cv::Mat &frmGray){
	bool b = false;

	for(int i = 0; i < frmGray.rows; i++){
		for(int j = 0; j < frmGray.cols; j++){
			if(frmGray.at<int>(i, j) < black) {
				topPoints.first = {i, j};
				b = true;
				break;
			}		
		}
		if(b != true) return false; // there is not any black point
		for(int j = frmGray.cols - 1; j >= 0; j--){
			if(frmGray.at<int>(i, j) < black) {
				topPoints.second = {i, j};
				break;
			}		
		}
	}

	// TBD

	for(int i = frmGray.rows; i >= 0; i--){
		for(int j = 0; j < frmGray.cols; j++){
			if(frmGray.at<int>(i, j) < black) {
				bottomPoints.first = {i, j};
				break;
			}		
		}
		for(int j = frmGray.cols - 1; j >= 0; j--){
			if(frmGray.at<int>(i, j) < black) {
				bottomPoints.second = {i, j};
				break;
			}		
		}
	}

	return true;
}
