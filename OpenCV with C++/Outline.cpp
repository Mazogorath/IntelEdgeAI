#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

//손바닥의 검출은 카메라와 조명의 한계로 불가능하나, 흑백사진을 불러오면 문제없이 작동함
//위의 경우 10행부터 36행까지 주석 처리 후 38행의 주석을 해제하면 됨

int main(void) {
	VideoCapture cap(0);	//기본 카메라 장치를 이용해 캡쳐

	Mat frame, palm, frame3;	//영상을 저장할 행렬들

	while (true) {
		cap >> frame;	//장치를 통해 얻은 영상을 행렬에 불러오기

		if (frame.empty()) {	//정상적으로 불러오지 못했으면
			cerr << "영상 불러오기 실패";
			return 0;	//프로그램 종료
		}

		imshow("카메라", frame);			//창을 열고 영상 출력

		int c = waitKey(10);		//10밀리초 단위
		if (c == 27)				//esc가 입력되면 루프 종료
			break;
		else if (c == ' ') {		//스페이스바 입력 시
			imwrite("palm.bmp", frame);	//현재 영상 캡쳐 후 저장
			palm = imread("palm.bmp");	//행렬에 저장한 사진 불러오기
			break;	//루프 종료
		}
	}
	destroyWindow("카메라");	//동영상 끄기2

	cvtColor(palm, palm, COLOR_BGR2GRAY);	//이진화 전 흑백화
	threshold(palm, palm, 200, 255, THRESH_BINARY | THRESH_OTSU);	//이진화
	
	//Mat palm = imread("contours.bmp", IMREAD_GRAYSCALE);	//동영상 대신 사진 이용을 위한 코드

	vector<vector<Point>> contour;	//외곽선 저장용 벡터
	vector<Vec4i> hierarchy;	//계층 정보 저장용 벡터
	findContours(palm, contour, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);	//외곽선 찾기
	for (int i = 0; i < contour.size(); i++) {	//저장된 외곽선들만큼 반복
		drawContours(palm, contour, i, Scalar(100, 100, 100), -1, LINE_8, hierarchy);	//BGR 100 100 100으로 칠하기
}
	
	imshow("palm", palm);

	waitKey();

	destroyAllWindows();		//모든 창 닫기
}