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
	cout << "�԰��� å�� �Է��ϼ���. �⵵�� -1 �Է��ϸ� ����";
	string name, author;
	int year = 0;
	int i = 0;
	while (1) {
		cout << "�⵵ >>";
		cin >> year;
		if (year == -1) break;
		cout << "å �̸� >>";
		cin >> name;
		cout << "���� >>";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> author;
		book[i++].setBook(name, author, year);
	}
	cout << "�԰�� å��" << i << "��";
	cout << "�˻��ϰ��� �ϴ� ���� �̸� �Է�";
	cin >> author;
	for (int x = 0; x < i; x++) {
		if (author == book[x].getAuthor()) book[x].getBook();
	}
	cout << "�˻��ϰ��� �ϴ� �⵵ �Է�";
	cin >> year;
	for (int x = 0; x < i; x++) {
		if (year == book[x].getYear()) book[x].getBook();
	}
}