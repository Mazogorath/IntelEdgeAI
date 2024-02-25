#include <iostream>
using namespace std;

class Queue {
	int front, back;
	int arr[5];
public:
	Queue() {
		front = back = -1;
		for (int i = 0; i < 5; i++) arr[i] = 0;
	}
	~Queue() { cout << "Queue 소멸자" << endl; }
	bool isFull() {
		if (front == 0 && back == 4) return true;
		else return false;
	}
	bool isEmpty() {
		if (front == -1 && back == -1) return true;
		else return false;
	}
	void enQueue(int value) {
		if (isFull()) cout << "여유 공간이 없습니다" << endl;
		else if (isEmpty()) {
			front = back = 0;
			arr[front] = value;
			cout << front << "번 공간에 " << arr[front] << "를 썼습니다" << endl;
		}
		else {
			int count = 0;
			if (front != 0) {
				for (int i = front; i <= back; i++) {
					arr[i - front] = arr[i];
					count++;
				}
				front = 0;
				back = count - 1;
			}
			else back++;
			arr[back] = value;
			cout << back << "번 공간에 " << arr[back] << "를 썼습니다" << endl;
		}
	}
	int deQueue() {
		int x = 0;
		if (isEmpty()) {
			return 0;
		}
		else if (front == back) {
			x = arr[front];
			arr[front] = 0;
			front = back = -1;
		}
		else {
			x = arr[front];
			arr[front++] = 0;
		}
		return x;
	}
};

int main(void) {
	Queue queue;
	int menu = 0;
	int value = 0;
	while (true) {
		cout << "1 isFull	2 isEmpty	3 enQueue	4 deQueue";
		cin >> menu;
		switch (menu) {
		case 1:
			if (queue.isFull()) cout << "가득 차있습니다" << endl;
			else cout << "여유 공간이 있습니다" << endl;
			break;
		case 2:
			if (queue.isEmpty()) cout << "비어 있습니다" << endl;
			else cout << "비어 있지 않습니다" << endl;
			break;
		case 3:
			cout << "삽입하고자 하는 데이터를 입력해주세요" << endl;
			cin >> value;
			queue.enQueue(value);
			break;
		case 4:
			if (queue.isEmpty()) cout << "큐가 비어있습니다" << endl;
			else cout << queue.deQueue() << "를 꺼내왔습니다" << endl;
			break;
		default:cout << "다시 입력해주세요" << endl;
		}
	}
}