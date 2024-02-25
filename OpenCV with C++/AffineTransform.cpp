#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(void) {
	Mat src = imread("lenna.bmp");

	if (src.empty()) {
		cerr << "열기 실패" << endl;
		return -1;
	}

	Point2f srcptr[3], dstptr[3];
	srcptr[0] = Point(0, 0);
	srcptr[1] = Point(src.cols - 1, 0);
	srcptr[2] = Point(src.cols - 1, src.rows - 1);
	dstptr[0] = Point(50, 50);
	dstptr[1] = Point(src.cols - 100, 100);
	dstptr[2] = Point(src.cols - 50, src.rows - 50);

	Mat M = getAffineTransform(srcptr, dstptr);

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}