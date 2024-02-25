#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void){
	Mat img = imread("circuit.bmp", IMREAD_COLOR);		//img = 메인보드 이미지
	Mat temp1 = imread("crystal.bmp", IMREAD_COLOR);	//temp1 = 크리스탈 이미지

	img = img + Scalar(50, 50, 50);						//img의 색상 변경

	Mat noise(img.size(), CV_32SC3);					//noise.size() = img.size(), signed int, 채널 3개
	randn(noise, 0, 10);								//noise 행렬을 평균 0, 표준편차 10의 난수로 채우기
	add(img, noise, img, Mat(), CV_8UC3);				//img = img + noise, unsigned character, 채널 3개

	Mat res, res_norm;									
	matchTemplate(img, temp1, res, TM_CCOEFF_NORMED);	//img와 temp1을 비교한 결과를 res에 저장
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);	//res_norm = res 정규화

	double maxv;										
	Point maxloc;
	minMaxLoc(res, 0, &maxv, 0, &maxloc);				//maxloc = res에서 maxv의 위치
	cout << maxv << endl;

	rectangle(img, Rect(maxloc.x, maxloc.y, temp1.cols, temp1.rows),	//img에 
		Scalar(0, 0, 255), 2);

	imshow("temp1", temp1);
	imshow("res_norm", res_norm);
	imshow("img", img);

	waitKey();
	destroyAllWindows();

}