#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main(void){
	VideoCapture cap(0);	//기본 카메라 장치를 이용해 캡쳐

	Mat frame1, frame2, frame3;	//영상을 저장할 행렬들

	while (true) {
		cap >> frame1;	//장치를 통해 얻은 영상을 행렬에 불러오기

		if (frame1.empty()) {	//정상적으로 불러오지 못했으면
			cerr << "영상 불러오기 실패";
			break;	//루프 종료
		}
		cvtColor(frame1, frame2, COLOR_BGR2GRAY);	//frame2는 그레이스케일
		threshold(frame2, frame3, 127, 255, THRESH_BINARY);	//흑백영상에 대해 127을 넘는 픽셀은 255로 만드는 이진화

		imshow("카메라", frame1);			//창을 열고 세 영상 출력
		imshow("그레이스케일", frame2);
		imshow("2진 화면", frame3);

		int c = waitKey(10);		//10밀리초 단위
		if (c == 27)				//esc가 입력되면 루프 종료
			break;
	}

	destroyAllWindows();		//모든 창 닫기
}