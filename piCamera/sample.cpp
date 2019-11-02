#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <ctime>
#include <opencv2/highgui.hpp>
#include <piImgWorker.h>



int main()
{
	int indxCamera = 0;
	std::time_t t_start, t_end;
	std::time(&t_start);
	int frames = 0, fps = 0;


	cv::VideoCapture cap(indxCamera);
	if (!cap.isOpened()) {
		std::cerr << "ERROR: Unable to open the camera" << std::endl;
		return 0;
	}

	cv::Mat frmTmp;
	
	cap.read(frmTmp);
	cv::Mat frmSrc(frmTmp.size(), CV_8UC1);
	cv::Mat frmTrh(frmTmp.size(), CV_8UC1);
	cv::Mat frmGray(frmTmp.size(),CV_8UC1);

	for (int i = 0; i <1; i++){
		cap.read(frmSrc);
		if (frmSrc.empty()) {
			std::cerr << "ERROR: Unable to grab from the camera" << std::endl;
			//break;
		}
		cv::cvtColor(frmSrc, frmGray, CV_BGR2GRAY);

		cv::imwrite ("./test" + std::to_string(i) + ".jpg", frmSrc);
	}

	
	piImgWorker imgWrk(40, false);

	while(true){
		cap.read(frmSrc);
		if (frmSrc.empty()) {
			std::cerr << "ERROR: Unable to grab from the camera" << std::endl;
			break;
		}

		//cv::inRange(frmGray, cv::Scalar(0, 0, 200, 0), cv::Scalar(180, 255, 255, 0), frmTrh);
		//cv::cvtColor(frm:Src, frmSrc, COLOR_BGR2HSV);
		//std::vector<cv::Mat> frmChannels(3);
		//cv::split(frmGray, frmChannels);
		/*
		if (imgWrk.Do(frmSrc)) {
			cv::circle(imgWrk.img, imgWrk.pntTopLeft, 10, cv::Scalar(200, 100, 50), 5); 
			cv::circle(imgWrk.img, imgWrk.pntTopRight, 10, cv::Scalar(200, 100, 50), 5); 
			cv::circle(imgWrk.img, imgWrk.pntBottomLeft, 10, cv::Scalar(200, 100, 50), 5); 
			cv::circle(imgWrk.img, imgWrk.pntBottomRight, 10, cv::Scalar(200, 100, 50), 5); 
		}
		cv::imshow("Gray", frmGray);
		cv::imshow("Trh", imgWrk.img);
		*/
		frames++;
		if ((frames % 100) == 0) {
			std::time(&t_end);
			int diff =std::difftime (t_end, t_start);	 
			fps = frames / diff; 
			std::cout << fps << " : " << diff << '\n'; 
			std::time(&t_start);
		}

		if(cv::waitKey(10) == 27) break;
	}
	cap.release();
	cv::destroyAllWindows();
	std::cout << "bye!" << std::endl;
	return 0;
}

