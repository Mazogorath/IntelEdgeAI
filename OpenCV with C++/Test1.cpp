#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

Mat src;						//원본 영상 저장용 행령
Mat blurred;					//필터 적용 영상 저장용 행렬
double sigma;					//표준편차

void on_track(int pos, void*);	//콜백함수 원형

int main(void) {
	src = imread("rose.bmp");	//이미지 읽어오기

	if (src.empty()) {			//읽기 실패 시
		cerr << "파일을 불러오지 못했습니다";
		return -1;				//프로그램 종료
	}

	imshow("src", src);			//원본 이미지 출력

	createTrackbar("Sigma", "src", 0, 8, on_track);	//원본 이미지에 Sigma라는 이름의 트랙바 생성
	setTrackbarMin("Sigma", "src", 1);				//트랙바의 최소값을 1로 설정 = 중간값이 4

	waitKey();					//키 입력 시
	return 0;					//정상 종료
}

void on_track(int pos, void*) {	//콜백함수 정의
	sigma = pos;				//표준편차 = 트랙바의 값
	GaussianBlur(src, blurred, Size(), sigma);		//가우시안 필터 적용, blurred에 저장
	float alpha = 1.f;								//언샤프 마스크 필터에 쓸 알파 값
	blurred = (1 + alpha) * src - alpha * blurred;	//blurred에 언샤프 마스크 필터 적용
	cout << "현재 Sigma 값 : " << sigma << endl;	//현재 Sigma값 출력
	imshow("blurred", blurred);						//blurred 출력
}