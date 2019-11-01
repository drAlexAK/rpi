#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <opencv2/highgui.hpp>
 
using namespace cv;
using namespace std;
 
int main(int argc,char ** argv)
{

  time_t start, end;
  int frmCount = 0;
  int fps=0;
  int indxCamera = 0;

  VideoCapture cap(indxCamera);
  if (!cap.isOpened()) {
    cerr << "ERROR: Unable to open the camera" << endl;
    return 0;
  }
 
  Mat frame;
  cout << "Start grabbing, press a key on Live window to terminate" << endl;
  while(true) {

  if (frmCount==0) time(&start); // Start time

    cap >> frame;
    if (frame.empty()) {
        cerr << "ERROR: Unable to grab from the camera" << endl;
        break;
    }

    frmCount++;
    if ((frmCount % 100) == 0)
    {
        time(&end);
	fps = frmCount/difftime (end, start);	
	cout << fps << '\n'; 
    }
  }
 
  cout << "Closing the camera" << endl;
  cap.release();
  destroyAllWindows();
  cout << "bye!" <<endl;
  return 0;
}

