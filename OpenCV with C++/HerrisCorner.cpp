#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void) {
	Mat img = imread("building.jpg", IMREAD_GRAYSCALE);

	Mat img2;
	cornerHarris(img, img2, 3, 3, 0.04);

	Mat img3;
	normalize(img2, img3, 0, 255, NORM_MINMAX, CV_8U);

	Mat img4;
	cvtColor(img, img4, COLOR_GRAY2BGR);

	for (int i = 0; i < img3.rows - 1; i++) {
		for (int j = 0; j < img3.cols - 1; j++) {
			if (img3.at<uchar>(i, j) > 120) {
				if (img3.at<uchar>(i, j) > img3.at<uchar>(i - 1, j) &&
					img3.at<uchar>(i, j) > img3.at<uchar>(i, j - 1) &&
					img3.at<uchar>(i, j) > img3.at<uchar>(i + 1, j) &&
					img3.at<uchar>(i, j) > img3.at<uchar>(i, j + 1))
					circle(img4, Point(i, j), 5, Scalar(255, 0, 0), 2);
			}
		}
	}

	imshow("img", img);
	imshow("img3", img3);
	imshow("img4", img4);
	imwrite("img5.jpg", img4);

	waitKey();
	destroyAllWindows();
}