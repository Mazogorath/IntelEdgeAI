#include <iostream>
#include <string>
using namespace std;

class Phone {
	string name; 
	string telnum;
	string address; 
public:	
	Phone(string name="", string telnum="", string address="") {
		this->name = name;
		this->telnum = telnum;
		this->address = address;
	}
	friend ostream& operator << (ostream& outs, Phone phone);
	friend istream& operator >> (istream& ins, Phone& phone);
};

ostream& operator << (ostream& outs, Phone phone) {
	outs << "(" << phone.name << ",";
	outs <<	phone.telnum << ",";
	outs <<	phone.address << ")";
	return outs;
} 

istream& operator >> (istream& ins, Phone& phone) {
	cout << "이름:";
	getline(ins, phone.name);
	cout << "전화번호:";
	getline(ins, phone.telnum);
	cout << "주소:";
	getline(ins, phone.address);
	return ins;
}

int main() {
	Phone girl, boy;
	cin >> girl >> boy;
	cout << girl << endl << boy << endl;
}