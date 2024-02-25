#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void) {
	Mat src = imread("pepper.bmp", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "오류";
		return -1;
	}

	Mat src2;
	cvtColor(src, src2, COLOR_BGR2YCrCb);

	vector<Mat> src3;
	split(src2, src3);

	equalizeHist(src3[0], src3[0]);

	Mat src4;
	merge(src3, src4);

	Mat src5;
	cvtColor(src4, src5, COLOR_YCrCb2BGR);

	imshow("src", src);
	imshow("src5", src5);

	waitKey();
	destroyAllWindows();

}