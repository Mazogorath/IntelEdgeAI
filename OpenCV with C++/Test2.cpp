#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
using namespace cv::dnn;	

const String model = "opencv_face_detector_uint8.pb";	//사용할 모델 파일
const String config = "opencv_face_detector.pbtxt";		//사용할 구성 파일

int main(void) {
	VideoCapture cap(0);								//기본 카메라 사용

	if (!cap.isOpened()) {								//카메라가 켜지지 않은 경우
		cerr << "영상을 불러오지 못했습니다";	
		return -1;										//프로그램 종료
	}
														//네트워크 = 딥러닝 모델, 신경망
	Net net = readNet(model, config);					//모델과 구성파일로 Net 객체 생성
	if (net.empty()) {									//못 가져왔으면
		cerr << "net을 불러오지 못했습니다";
		return -1;										//프로그램 종료
	}

	Mat frame, frame2;									//영상을 담을 행렬 2개
	while (1) {
		cap >> frame;									//영상 담기
		if (frame.empty()) break;						//영상 못 가져왔으면 루프 종료
		cvtColor(frame, frame2, COLOR_BGR2GRAY);		//영상2 = 흑백 영상1
		Mat blob = blobFromImage(frame, 1,				//frame 영상을 이용해 네트워크 입력 블롭 객체 생성
			Size(300, 300), Scalar(104, 177, 123));		//배율 1, 입력 크기 Size, 이미지에서 뺄 평균값 Scalar = 정규화
														
		net.setInput(blob);								//전처리된 이미지를 네트워크의 입력으로 사용
		Mat res = net.forward();						//네트워크 실행, res에 저장

		Mat detect(res.size[2], res.size[3],			//행렬 만들기, 사이즈 = res의 행과 열
			CV_32FC1, res.ptr<float>());				//32bit, float, channel 1개, res의 데이터를 복사


		for (int i = 0; i < detect.rows; i++) {			//detect 행렬의 열만큼 반복
			float confidence = detect.at<float>(i, 2);	//신뢰도 = detect의 i행 2열 원소
			if (confidence < 0.5) break;				//신뢰도 0.5 미만이면 중단


			int x1 = cvRound(detect.at<float>(i, 3) * frame.cols);	//x1 = detect의 i행 3열과 원본 영상의 열을 곱한 후 반올림한 값
			int y1 = cvRound(detect.at<float>(i, 4) * frame.rows);	//y1 = i행 4열과 영상의 행
			int x2 = cvRound(detect.at<float>(i, 5) * frame.cols);	//x2 = i행 5열과 영상의 행
			int y2 = cvRound(detect.at<float>(i, 6) * frame.rows);	//y2 = i행 6열과 영상의 행

			rectangle(frame, Rect(Point(x1, y1), Point(x2, y2)), Scalar(0, 255, 0));	//x1y1, x2y2를 좌표로 갖는 녹색 사각형 그리기

			String label = format("Face : %4.3f", confidence);							//label = 0000.000 형태의 신뢰도
			putText(frame, label, Point(x1, y1 - 1), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 0));		//영상에 위의 값 표시

			threshold(frame2, frame2, 0, 255, THRESH_BINARY | THRESH_OTSU);	//영상2 이진화, 임계값 자동 결정
			morphologyEx(frame2, frame2, MORPH_OPEN, Mat());				//영상2 모폴로지 열기 연산
		}

		imshow("frame", frame);			//영상1 출력
		imshow("frame2", frame2);		//영상2 출력
		if (waitKey(1) == 27) break;	//ESC 누르면 종료, 1ms마다 검사

	}
	return 0;							//정상 종료
}