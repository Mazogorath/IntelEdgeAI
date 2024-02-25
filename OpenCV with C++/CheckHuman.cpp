#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void) {
	VideoCapture cap("vtest.avi");

	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	Mat frame;
	while (true) {
		cap >> frame;

		if (frame.empty()) break;
		
		vector<Rect> detected;
		hog.detectMultiScale(frame, detected);

		for (Rect r : detected) {
			Scalar c(rand() % 255, rand() % 255, rand() % 255);
			rectangle(frame, r, c, 3);
		}
		imshow("frame", frame);

		if (waitKey(10) == 27) break;
	}
	return 0;
}