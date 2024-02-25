#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void) {
	VideoCapture cap(0);

	if (!cap.isOpened()){
		cerr << "Cam x";
		return -1;
	}

	QRCodeDetector qrcd;
	Mat frame;
	
	while (1) {
		cap >> frame;

		vector<Point> vec;

		if (qrcd.detect(frame, vec)) {
			rectangle(frame, vec[0], vec[2], Scalar(255, 0, 255), 2);
			String info = qrcd.decode(frame, vec);
			putText(frame, info, Point(10, 30), 
				FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 2);
			imshow("frame", frame);
			cout << "Decoded info: " << info << endl;
		}

		imshow("frame", frame);
		if (waitKey(10) == 27) break;
	}
	return 0;
}