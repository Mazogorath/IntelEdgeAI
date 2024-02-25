#include <iostream>
#include <string>
using namespace std;

class SortedArray {
	int size;
	int *p;
	void sort();
public:
	SortedArray();
	SortedArray(SortedArray& src);
	SortedArray(int p[], int size);
	~SortedArray();
	SortedArray operator + (SortedArray& op2);
	SortedArray& operator = (const SortedArray& op2);
	void show();
};

SortedArray::SortedArray() {
	p = NULL;
	size = 0;
}
SortedArray::~SortedArray() {
	if (p != NULL)
		delete[] p;
}

SortedArray::SortedArray(int p[], int size) {
	this->size = size;
	this->p = new int[size];
	for (int i = 0; i < size; i++) {
		this->p[i] = p[i];
	}

	sort();
}

SortedArray::SortedArray(SortedArray& src) {
	this->size = src.size;
	if (src.size == 0) {
		this->p = NULL;
	}
	else {
		this->p = new int[this->size];
		for (int i = 0; i < this->size; i++) {
			this->p[i] = src.p[i];
		}
	}
}

void SortedArray::sort() {
	if (p == NULL || size == 0)
		return;
	for (int i = 0; i < size - 1; i++) {
		for (int j = i; j < size - 1; j++) {
			if (p[j] > p[j + 1]) {
				int temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
}

void SortedArray::show() {
	cout << "배열 출력 : ";
	for (int i = 0; i < size; i++) {
		cout << p[i] << ' ';
	}
	cout << endl;

}

SortedArray& SortedArray::operator = (const SortedArray& op2) {
	if (p != NULL) {
		delete[] p;
	}

	size = op2.size;
	if (size == 0) {
		p = NULL;
		return *this;
	}

	p = new int[size];
	for (int i = 0; i < size; i++)
		p[i] = op2.p[i];
	return *this;
}

SortedArray SortedArray::operator + (SortedArray& op2) {
	SortedArray temp;

	if (this->size == 0) {
		temp.size = op2.size;
		if (temp.size == 0) {
			temp.p = NULL;
		}
		else {
			temp.p = new int[temp.size];
			for (int i = 0; i < temp.size; i++)
				temp.p[i] = op2.p[i];
		}
	}
	else if (op2.size == 0) {
		temp.size = this->size;
		temp.p = new int[temp.size];
		for (int i = 0; i < temp.size; i++)
			temp.p[i] = this->p[i];
	}
	else {
		temp.size = this->size + op2.size;
		temp.p = new int[temp.size];
		int i;
		for (i = 0; i < this->size; i++)
			temp.p[i] = this->p[i];
		for (int j = 0; j < op2.size; j++)
			temp.p[i + j] = op2.p[j];
	}
	temp.sort();
	return temp;
}

int main() {
	int n[] = { 2, 20, 6 };
	int m[] = { 10, 7, 8, 30 };
	SortedArray a(n, 3), b(m, 4), c;
	
	c = a + b;

	a.show();
	b.show();
	c.show();
}