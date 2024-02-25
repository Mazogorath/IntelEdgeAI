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
	cout << "���� ���� >> ";
	cin >> number;
	if(size < 1)
		return 0;

	circle = new Circle[size];
	int radius;
	for(int i=0; i<size; i++) {
		cout << "�� " << i+1 << "�� ������ >> ";
		cin >> radius;
		circle[i].setRadius(radius);
	}
	int count = 0;
	for(int i=0; i<size; i++) {
		if(circle[i].getArea() > 100) {
			count++; 
		}
	}
	cout << "������ 100���� ū ���� " << count << "�� �Դϴ�" << endl;
	delete [] circle;
}

