#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <stdlib.h>
//#include <opencv2/highgui.hpp>

//using namespace cv;
//using namespace std;


class piImgWorker {
private:
	int black = 80;
public:

/*struct Point{
	int row;
	int col;
	Point(){
		row = 0;
		col = 0;
	}
	Point(int _row, int _col){
		row = _row;
		col = _col;
	}
};*/
	//struct Point;
	std::pair<cv::Point, cv::Point> topPoints;
	std::pair<cv::Point, cv::Point> bottomPoints;
	bool getPoint(cv::Mat &frmGray);
	piImgWorker(int _black);
};
