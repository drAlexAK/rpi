#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <opencv2/highgui.hpp>
#include <piImgWorker.h>



int main()
{
	int indxCamera = 0;

	cv::VideoCapture cap(indxCamera);
	if (!cap.isOpened()) {
		std::cerr << "ERROR: Unable to open the camera" << std::endl;
		return 0;
	}

	cv::Mat frmSrc, frmTrh, frmGray;

	for (int i = 0; i <1; i++){
		cap.read(frmSrc);
		if (frmSrc.empty()) {
			std::cerr << "ERROR: Unable to grab from the camera" << std::endl;
			//break;
		}
		cv::cvtColor(frmSrc, frmGray, CV_BGR2GRAY);

		cv::imwrite ("./test" + std::to_string(i) + ".jpg", frmSrc);
	}

	
	piImgWorker imgWrk(40);

	while(true){
		cap.read(frmSrc);
		if (frmSrc.empty()) {
			std::cerr << "ERROR: Unable to grab from the camera" << std::endl;
			break;
		}
		cv::cvtColor(frmSrc, frmGray, cv::COLOR_BGR2GRAY);  //cv::COLOR_BGR2HSV  
		//cv::cvtColor(frmSrc, frmGray, cv::COLOR_BGR2HLS);  //cv::COLOR_BGR2HSV  
		//cv::GaussianBlur(frmGray, frmGray, cv::Size(7, 7), 0, 0);
		cv::threshold(frmGray, frmTrh, 100, 255, cv::THRESH_BINARY);
		//cv::inRange(frmGray, cv::Scalar(0, 0, 200, 0), cv::Scalar(180, 255, 255, 0), frmTrh);
		//cv::cvtColor(frmSrc, frmSrc, COLOR_BGR2HSV);
		//std::vector<cv::Mat> frmChannels(3);
		//cv::split(frmGray, frmChannels);
		if (imgWrk.getPoint(frmTrh)) {
			cv::circle(frmTrh, imgWrk.topPoints.first, 10, cv::Scalar(200, 100, 50), 5); 
			cv::circle(frmTrh, imgWrk.topPoints.second, 10, cv::Scalar(200, 100, 50), 5); 
			cv::circle(frmTrh, imgWrk.bottomPoints.first, 10, cv::Scalar(200, 100, 50), 5); 
			cv::circle(frmTrh, imgWrk.bottomPoints.second, 10, cv::Scalar(200, 100, 50), 5); 
		}
		cv::imshow("Gray", frmGray);
		cv::imshow("Trh", frmTrh);
		//int i = 0 ;
		//for(auto ch : frmChannels){
		//	cv::imshow(std::to_string(i), ch);
		//	i++;
		//}
		if(cv::waitKey(10) == 27) break;
	}
	cap.release();
	cv::destroyAllWindows();
	std::cout << "bye!" << std::endl;
	return 0;
}

