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
	cout << "�̸�:";
	getline(ins, phone.name);
	cout << "��ȭ��ȣ:";
	getline(ins, phone.telnum);
	cout << "�ּ�:";
	getline(ins, phone.address);
	return ins;
}

int main() {
	Phone girl, boy;
	cin >> girl >> boy;
	cout << girl << endl << boy << endl;
}