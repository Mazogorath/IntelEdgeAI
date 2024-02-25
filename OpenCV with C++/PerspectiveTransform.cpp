#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

Mat src, dst;
Point2f srcQuad[4], dstQuad[4];

void onMouse(int event, int x, int y, int flags, void*);

int main(void) {
	src = imread("card.bmp");
	
	namedWindow("card");
	setMouseCallback("card", onMouse);
	
	imshow("card", src);
	waitKey();
}
void onMouse(int event, int x, int y, int flags, void*) {
	static int count = 0;

	if (event == EVENT_LBUTTONDOWN) {
		if (count < 4) {
			srcQuad[count++] = Point2f(x, y);
			circle(src, Point(x, y), 5, Scalar(0, 0, 0), -1);
			imshow("card", src);
		}
		if (count == 4) {
			int w = 200, h = 300;
			dstQuad[0] = Point2f(0, 0);
			dstQuad[1] = Point2f(w - 1, 0);
			dstQuad[2] = Point2f(w - 1, h - 1);
			dstQuad[3] = Point2f(0, h - 1);
			Mat m = getPerspectiveTransform(srcQuad, dstQuad);
			warpPerspective(src, dst, m, Size(w, h));

			imshow("dst", dst);
		}
	}
}