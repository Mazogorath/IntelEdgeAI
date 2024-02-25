#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;

class Nation {
	string nation;
	string capital;
public:
	void setNation(string nation) { this->nation = nation; }
	void setCapital(string capital) { this->capital = capital; }
	Nation() : Nation("나라", "수도"){}
	Nation(string nation, string capital) { this->nation = nation; this->capital = capital; }
	string getNation() { return nation; }
	string getCapital() { return capital; }
};
int main(void) {
	vector<Nation> v;
	int arraysize = 10;
	Nation*n = new Nation[arraysize];
	
	string nation, capital;
	int menu = 0;
	int rand = 0;
	int i = 0;

	cout << "수도 맞추기";
	
	while (1) {
		cout << "1 입력		2 퀴즈		3 종료";
		cin >> menu;
		if (menu == 1) {
			while (1){
				cout << v.size() << "개 국가 입력됨\n국가와 수도 입력";
			cin >> nation;
			cin >> capital;
			if (nation == "no" && capital == "no") {
				cout << "장비를 정지합니다";
				break;
			}
			for (i = 0; i < v.size(); i++) {
					if (nation == n[i].getNation()) {
						cout << "이미 존재함";
						continue;
					}
					if (capital == n[i].getCapital()) {
						cout << "이미 존재함";
						continue;
					}
			}
			Nation n(nation, capital);
			v.push_back(n);
			}
		}
		if (menu == 2) {
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<int> dis(0, v.size()-1);
			while (1){
				rand = dis(gen);
				cout << v[rand].getNation();
				cin >> capital;
				if (capital == v[rand].getCapital()) cout << "YES\n";
				else if (capital == "exit") break;
				else cout << "NO";
			}
		}
		if (menu == 3) break;
	}
}