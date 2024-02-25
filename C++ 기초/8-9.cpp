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
	~Console() { delete [] booking; cout << "소멸자"; }
	void Menu() {
		cout << "예약:1, 취소:2, 보기:3, 끝내기:4 >>";
		cin >> menu;
		switch (menu) {
		case 1:reservMenu(); break;
		case 2:reservMenu(); break;
		case 3:viewMenu(); break;
		case 4:cout << "종료"; break;
		default:break;
		}
	}
	void reservMenu() {
		string name; int time; int seat;
		cout << "07시:1, 12시:2, 17시:3 >>";
		cin >> time;
		cout << "좌석 번호 >>";
		cin >> seat;
		cout << "이름 입력";
		cin.ignore();
		getline(cin, name, '\n');
		if (menu == 1) booking[time-1][seat-1].setName(name);
		else booking[time - 1][seat - 1].setName("---");
		menu = 0;
		Menu();
	}
	void viewMenu() {
		unsigned int i = 0;
		cout << "07시:   ";
		for (i = 0; i < 8; i++) {
			cout << booking[0][i].showName() << "   ";
		}
		cout << endl << "12시:   ";
		for (i = 0; i < 8; i++) {
			cout << booking[1][i].showName() << "   ";
		}
		cout << endl << "17시:   ";
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
