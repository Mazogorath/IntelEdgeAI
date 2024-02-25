#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

Mat img;	//스크린샷 저장용 객체
Mat frame;	//영상 프레임 객체
Point cordinate1, cordinate2(-1, -1);	//스크린샷 저장용 좌표 객체

void onMouse(int event, int x, int y, int flags, void*);

int main(void) {
	VideoCapture cap(0);	//기본 카메라 이용

	if (!cap.isOpened()) {	//카메라 불러오기 실패 시
		cerr << "Camera open failed!" << endl;
		return 0;
	}

	while (true) {
		cap >> frame;		//카메라에서 프레임 가져오기
		if (frame.empty())
			break;

		setMouseCallback("frame", onMouse);	//마우스 기능 활성화
		imshow("frame", frame);

		if (waitKey(10) == 27) // ESC key
			break;
	}

	destroyAllWindows();
}

void onMouse(int event, int x, int y, int flags, void*) {
	switch (event) {
	case EVENT_LBUTTONDOWN:		//마우스 좌클릭
		cordinate1 = Point(x, y);	//시작 좌표 저장
		break;
	case EVENT_LBUTTONUP:		//마우스 우클릭
		cordinate2 = Point(x, y);	//종료 좌표 저장
		img = frame(Rect(cordinate1, cordinate2));	//두 좌표 사이의 이미지 저장
		rectangle(frame, cordinate1, cordinate2, Scalar(0, 0, 0));
		imwrite("Captured.bmp", img);
		namedWindow("Captured");
		imshow("Captured", img);
		break;
	case EVENT_MOUSEMOVE:	//마우스 움직임
		if (flags & EVENT_FLAG_LBUTTON) {	//좌클릭 + 이동
			cordinate2 = Point(x, y);	
		}
		break;
	default: break;
	}
}