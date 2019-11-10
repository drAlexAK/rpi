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
	cv::Scalar sclText(128, 128, 128);
	cv::Scalar sclCir(200, 100, 50);
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

		if (imgWrk.Do(frmSrc)) {
			cv::circle(imgWrk.img, imgWrk.pntTopLeft, 10, sclCir , 5); 
			cv::circle(imgWrk.img, imgWrk.pntTopRight,    10, sclCir, 5); 
			cv::circle(imgWrk.img, imgWrk.pntBottomLeft,  10, sclCir , 5); 
			cv::circle(imgWrk.img, imgWrk.pntBottomRight, 10, sclCir, 5); 
			cv::putText(imgWrk.img, std::to_string(imgWrk.degDeviationFromCenter) + " " + std::to_string(imgWrk.degRelativeDeviation),
					cv::Point(50,50), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, sclText, 1, CV_AA);
			cv::putText(imgWrk.img,"tl: " + std::to_string(imgWrk.pntTopLeft.x) + ", " + std::to_string(imgWrk.pntTopLeft.y), cv::Point(50, 60), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, sclText, 1, CV_AA);
			cv::putText(imgWrk.img,"tr: " + std::to_string(imgWrk.pntTopRight.x) + ", " + std::to_string(imgWrk.pntTopRight.y), cv::Point(140, 60), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, sclText, 1, CV_AA);
			cv::putText(imgWrk.img,"bl: " + std::to_string(imgWrk.pntBottomLeft.x) + ", " + std::to_string(imgWrk.pntBottomLeft.y), cv::Point(50, 70), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, sclText, 1, CV_AA);
			cv::putText(imgWrk.img,"br: " + std::to_string(imgWrk.pntBottomRight.x) + ", " + std::to_string(imgWrk.pntBottomRight.y), cv::Point(140, 70), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, sclText, 1, CV_AA);
		}
		cv::imshow("Gray", frmGray);
		cv::imshow("Trh", imgWrk.img);

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

