#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;



int main(void) {

	ifstream fin("C:\\windows\\system.ini");
	if (!fin) {
		return 0;
	}
	ofstream fout("C:\\temp\\2.txt");
	if (!fout) {
		return 0;
	}
	int menu = 0;
	cout << "���� ��ȣ�� �Է��ϼ���. -1 �Է� �� ����";
	vector<string> v;
	string line;
	while (getline(fin, line)) {
		v.push_back(line);
	}

	while (1) {
		cin >> menu;
		cout << v.at(menu);
	}
}