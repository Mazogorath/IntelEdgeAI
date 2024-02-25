#include <iostream>
#include <string>
using namespace std;

class Book {
	string name, author;
	int year;
public:
	void setBook(string name, string author, int year) { this->name = name; this->author = author; this->year = year; }
	string getName() { return name; }
	string getAuthor() { return author; }
	int getYear() { return year; }
	void getBook() { cout << name << author << year; }

};

int main(void) {
	Book* book = new Book [10];
	cout << "입고할 책을 입력하세요. 년도에 -1 입력하면 종료";
	string name, author;
	int year = 0;
	int i = 0;
	while (1) {
		cout << "년도 >>";
		cin >> year;
		if (year == -1) break;
		cout << "책 이름 >>";
		cin >> name;
		cout << "저자 >>";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> author;
		book[i++].setBook(name, author, year);
	}
	cout << "입고된 책은" << i << "권";
	cout << "검색하고자 하는 저자 이름 입력";
	cin >> author;
	for (int x = 0; x < i; x++) {
		if (author == book[x].getAuthor()) book[x].getBook();
	}
	cout << "검색하고자 하는 년도 입력";
	cin >> year;
	for (int x = 0; x < i; x++) {
		if (year == book[x].getYear()) book[x].getBook();
	}
}