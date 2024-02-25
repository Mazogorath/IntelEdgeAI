#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;



int main(void) {

	ifstream fin("C:\\windows\\system.ini");
	if (!fin) {
		cout << "읽을 수 없음";
		return 0;
	}
	ofstream fout("C:\\temp\\1.txt");
	if (!fout) {
		cout << "읽지 못함";
		return 0;
	}
	
	fin.seekg(0, ios::end);
	int ch = fin.tellg();
	fin.seekg(0, ios::beg);

	for (int i = 0; i < ch; i++) {
		int ch = fin.get();
		fout << hex << setw(2) << setfill('0') << ch << ' ';
	}
	fin.close();
	fout.close();

}