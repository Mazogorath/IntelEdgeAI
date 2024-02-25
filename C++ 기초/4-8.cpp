#include <iostream>
using namespace std;

class Circle {
	int radius;
public:
	void setRadius(int radius);
	double getArea();
};

void Circle::setRadius(int radius) {
	this->radius = radius;
}

double Circle::getArea() {
	return 3.14*radius*radius;
}

int main() {
	Circle *circle;
	int number;
	cout << "원의 개수 >> ";
	cin >> number;
	if(size < 1)
		return 0;

	circle = new Circle[size];
	int radius;
	for(int i=0; i<size; i++) {
		cout << "원 " << i+1 << "의 반지름 >> ";
		cin >> radius;
		circle[i].setRadius(radius);
	}
	int count = 0;
	for(int i=0; i<size; i++) {
		if(circle[i].getArea() > 100) {
			count++; 
		}
	}
	cout << "면적이 100보다 큰 원은 " << count << "개 입니다" << endl;
	delete [] circle;
}

