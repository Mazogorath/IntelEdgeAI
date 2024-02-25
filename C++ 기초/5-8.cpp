#include <iostream>
using namespace std;

class MyIntStack {
	int *p;
	int size;
	int tos;
public:
	MyIntStack();
	MyIntStack(int size);
	MyIntStack(const MyIntStack& s);
	~MyIntStack();

	bool push(int n);
	bool pop(int &n);
};

MyIntStack::MyIntStack() { 
	size = 10; 
	tos = 0;
	p = new int [size];
}

MyIntStack::MyIntStack(int size) {
	this->size = size;
	tos = 0;
	p = new int [size];
}

MyIntStack::~MyIntStack() {
	if(p) 
		delete [] p;
}

MyIntStack::MyIntStack(MyIntStack& src) {
	size = src.size;
	tos = src.tos;
	p = new int [size];
	for(int i=0; i<size; i++)
		p[i] = src.p[i];
}

bool MyIntStack::push(int n) {
	if(tos == size) 
		return false;
	p[tos] = n;
	tos++;
	return true;
}

bool MyIntStack::pop(int& n) {
	if(tos == 0)
		return false;
	tos--;
	n = p[tos];
	return true;
}

int main() {
	MyIntStack a(10);
	a.push(10);
	a.push(20);

	MyIntStack b = a;
	b.push(30);

	int n;
	a.pop(n);
	cout << "a¿¡¼­ ²¨³½ °ª " << n << endl;
	b.pop(n);
	cout <<  "b¿¡¼­ ²¨³½ °ª " << n << endl;
}