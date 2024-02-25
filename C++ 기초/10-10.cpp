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
	Nation() : Nation("����", "����"){}
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

	cout << "���� ���߱�";
	
	while (1) {
		cout << "1 �Է�		2 ����		3 ����";
		cin >> menu;
		if (menu == 1) {
			while (1){
				cout << v.size() << "�� ���� �Էµ�\n������ ���� �Է�";
			cin >> nation;
			cin >> capital;
			if (nation == "no" && capital == "no") {
				cout << "��� �����մϴ�";
				break;
			}
			for (i = 0; i < v.size(); i++) {
					if (nation == n[i].getNation()) {
						cout << "�̹� ������";
						continue;
					}
					if (capital == n[i].getCapital()) {
						cout << "�̹� ������";
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