#include <iostream>
#include <string>
using namespace std;

class Book {
	string name;
	int seat;
	int time;
public:
	Book() { name = "---"; seat = 0; }
	void setSeat(int seat) { this->seat = seat; }
	void setTime(int time) { this->time = time; }
	void setName(string name) { this->name = name; }
	string showName() { return name; }
};

class Console {
	int menu;
	Book** booking;
public:
	Console() {
		menu = 0; booking = new Book * [3];
		for (int i = 0; i < 3; i++) booking[i] = new Book[8];
	}
	~Console() { delete [] booking; cout << "�Ҹ���"; }
	void Menu() {
		cout << "����:1, ���:2, ����:3, ������:4 >>";
		cin >> menu;
		switch (menu) {
		case 1:reservMenu(); break;
		case 2:reservMenu(); break;
		case 3:viewMenu(); break;
		case 4:cout << "����"; break;
		default:break;
		}
	}
	void reservMenu() {
		string name; int time; int seat;
		cout << "07��:1, 12��:2, 17��:3 >>";
		cin >> time;
		cout << "�¼� ��ȣ >>";
		cin >> seat;
		cout << "�̸� �Է�";
		cin.ignore();
		getline(cin, name, '\n');
		if (menu == 1) booking[time-1][seat-1].setName(name);
		else booking[time - 1][seat - 1].setName("---");
		menu = 0;
		Menu();
	}
	void viewMenu() {
		unsigned int i = 0;
		cout << "07��:   ";
		for (i = 0; i < 8; i++) {
			cout << booking[0][i].showName() << "   ";
		}
		cout << endl << "12��:   ";
		for (i = 0; i < 8; i++) {
			cout << booking[1][i].showName() << "   ";
		}
		cout << endl << "17��:   ";
		for (i = 0; i < 8; i++) {
			cout << booking[2][i].showName() << "   ";
		}
		menu = 0;
		cout << endl;
		Menu();
	}
	friend Book;
};

int main(void) {
	Console* console = new Console[3];
	while (1) {
		console->Menu();
	}
}
