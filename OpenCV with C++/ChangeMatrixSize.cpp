#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(void) {
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);

	Mat img1f;
	img1.convertTo(img1f, CV_32FC1); //lenna.bmp를 32비트 실수화

	uchar data1[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	Mat mat1(3, 4, CV_8UC1, data1); //data1을 3x4 행렬로, unsigned char
	Mat mat2 = mat1.reshape(0, 1); //mat2 = mat1을 1x12로 만든 행렬

	cout << mat1 << endl << mat2 << endl;

	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255; //mat3 = 1x4 행렬, unsigned char, 1로 가득 채운 후 모든 원소에 255 곱하기
	mat1.push_back(mat3); //mat1 아래에 mat3을 추가
	cout << mat1 << endl;

	mat1.resize(6, 100); //mat1을 6행으로 변경, 추가된 행의 원소들을 100으로 초기화
	cout << mat1 << endl;
}