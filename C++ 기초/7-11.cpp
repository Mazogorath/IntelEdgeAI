#include <iostream>
using namespace std;

class Stack {
	int size;
	int* mem;
	int tos;
public:
	Stack(int size = 10) {
		this->size = size;
		mem = new int [size];
		tos = -1;
	}
	~Stack() { delete [] mem; }
	Stack& operator << (int n);
	Stack& operator >> (int& n);
	bool operator ! ();
};

Stack& Stack::operator << (int n) {
	if(tos == size-1) {
		return *this;
	}
	tos++;
	mem[tos] = n;
	return *this;
} 

Stack& Stack::operator >> (int& n) {
	if(tos == -1) {
		return *this;
	} 
	n = mem[tos];
	tos--;
	return *this;
} 

bool Stack::operator ! () {
	if(tos == -1)
		return true;
	else
		return false;
}

int main() {
	Stack stack;
	stack << 3 << 5 << 10;
	while(true) {
		if(!stack) break;
		int x;
		stack >> x;
		cout << x << ' ';
	}
	cout << endl;
}