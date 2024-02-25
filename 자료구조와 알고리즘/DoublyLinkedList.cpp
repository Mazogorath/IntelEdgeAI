#include <iostream>
using namespace std;

class Node {
	int key;	//노드 번호
	int data;	//노드 데이터
	Node* next;	//다음 노드의 주소
	Node* prev; //이전 노드의 주소
	Node* head;	//첫번째 노드를 가리킴
public:
	Node() {		//기본 생성자
		key = 0;
		data = 0;
		next = NULL;
		prev = NULL;
		head = NULL;
	}
	Node(int k, int d) {
		key = k;
		data = d;
		next = NULL;
		prev = NULL;
	}
	~Node() {

	}
	Node* nodeExists(int k) {		//k번 노드 확인용 함수	
		Node* ptr = head;
		if (ptr == NULL)			//노드가 하나도 없는 경우
			return ptr;				//곧바로 반환
		while (ptr != NULL) {		//노드가 실존하는 동안
			if (ptr->key == k) {	//k번 노드를 찾았다면
				//cout << "nodeExists 함수에서 k가 key인 ptr 반환" << endl;
				return ptr;			//ptr 반환
			}
			else if (ptr == NULL) {	//k번 노드가 존재하지 않는다면
				//cout << "nodeExists 함수에서 NULL을 반환" << endl;
				return ptr;
			}
			ptr = ptr->next;		//다음 노드로 이동
			//cout << "NE, ptr = ptr->next" << endl;
		}
		return ptr;					//while문의 비정상 종료를 위한 안전장치
	}
	void appendNode(Node* n) {		//맨 뒤에 노드 n 삽입 함수
		if (head == NULL) {			//노드가 하나도 없는 경우
			head = n;				//n을 첫번째 노드로
			n->next = NULL;			//n의 다음 주소는 NULL로
			n->prev = NULL;
			//cout << "appendNode 에서 head = NULL임을 확인" << endl;
			return;					//함수 종료
		}
		if (nodeExists(n->key) != NULL) {	//n의 key값을 가진 노드가 이미 존재하면
			cout << "해당 키 값의 노드가 존재합니다" << endl;
			return;
		}
		else {						//이미 노드가 있고 중복이 아닌 경우
			Node* ptr = head;		//ptr이 첫 노드를 가리킴
			Node* prev = NULL;	
			while (ptr->next != NULL) {		//링크의 끝으로 갈 때까지 루프
				prev = ptr;					//prev는 ptr의 이전 노드를 가리킴
				ptr = ptr->next;			//ptr이 다음 노드를 가리킴
				//cout << "AN, ptr = ptr->next" << endl;
			}
			ptr->next = n;			//n을 링크의 마지막에 배치
			n->next = NULL;			//n이 마지막이니 n의 다음은 NULL
			n->prev = prev;			//n의 이전 노드
		}
	}
	void prependNode(Node* n) {		//맨 앞에 노드 n 삽입 함수
		if (head == NULL) {			//노드가 하나도 없다면
			head = n;				//n을 첫번째 노드로
			n->next = NULL;			//n의 다음 주소는 NULL로
			return;
		}
		if (nodeExists(n->key) != NULL) {	//n과 중복되는 key값의 노드가 존재
			cout << "해당 키 값의 노드가 존재합니다" << endl;
		}
		else {
			n->next = head;		//맨 앞에 있던 노드가 n의 다음 주소
			head = n;			//맨 앞에는 n을
		}
	}
	void insertNode(int k, Node* n) {	//k번 노드 뒤에 노드 n 삽입 함수
		Node* ptr = nodeExists(k);		//ptr = k번 노드 or NULL
		if (ptr == NULL) {				//k번 노드가 없다면
			cout << k << "에 해당하는 키 값의 노드가 존재하지 않습니다" << endl;
		}
		else {							//k번 노드가 있다면 노드 n은 기존의 ptr과 ptr->next 사이에
			n->next = ptr->next;
			n->prev = ptr;
			ptr->next = n;
			n->next->prev = n;			//n의 다음 노드의 이전 노드는 n
		}
	}
	void deleteNode(int k) {		//k번 노드 지우기
		if (nodeExists(k) == NULL) {	//k번 노드가 없으면
			cout << k << "에 해당하는 키 값의 노드가 존재하지 않습니다";
			return;
		}
		else {							//k번 노드가 있으면
			Node* ptr = head;			//지울 노드를 가리킴
			Node* tmp = NULL;			//지울 노드의 이전 노드를 가리킴
			while (ptr->key != k) {		//ptr이 k번 노드를 가리킬 때까지 루프
				tmp = ptr;
				ptr = ptr->next;
			}
			if (ptr == head) {			//지우고자 하는 노드가 첫 노드면
				head = ptr->next;		//첫 노드 바꾸기
				delete ptr;
			}
			else {						//그 외
				tmp->next = ptr->next;	//k번 노드 근처의 노드를 서로 연결하기
				ptr->prev = tmp;		
				delete ptr;				//k번 노드 지우기
			}
		}
	}
	void updateNode(int k, int d) {		//k번 노드의 데이터 교체 함수
		Node* ptr = nodeExists(k);		//ptr = k번 노드 or NULL
		if (ptr == NULL) {				//ptr이 NULL이면
			cout << k << "에 해당하는 키 값의 노드가 존재하지 않습니다";
			return;
		}
		else {							//k번 노드이면
			ptr->data = d;				//k번 노드의 데이터 = d
		}
	}
	void printList() {					//리스트 안의 노드 출력 함수
		if (head == NULL) {				//안에 노드가 없다면
			cout << "노드가 아예 없어요" << endl;
			return;
		}
		else {							//노드가 있으면
			Node* ptr = head;			//ptr = 첫 노드
			while (ptr != NULL) {		//리스트의 끝까지 반복
				cout << "key : " << ptr->key << ", data : " << ptr->data << endl;	//노드 정보 표시
				ptr = ptr->next;		//다음 노드로 이동
			}
			cout << "이상입니다." << endl;
		}
	}

	void setKey(int key) {				//key setter
		this->key = key;				
	}
	void setData(int data) {			//data setter
		this->data = data;
	}
};

int main(void) {
	Node node;							//객체 생성
	int option = 0, key = 0, data = 0, key1 = 0;	//option = 메뉴 입력용 변수, key/data = 새로운 노드의 데이터, key1 = insert 함수의 위치 지정용 변수
	while (true) {
		cout << "1 append   2 prepend   3 insert   4 delete   5 update   6 print   7 clear   8 exit" << endl;
		cin >> option;
		Node* n1 = new Node();			//삽입할 노드를 동적으로 생성
		switch (option) {
		case 1:
			cout << "key and data" << endl;		//append
			cin >> key >> data;
			n1->setData(data);
			n1->setKey(key);
			node.appendNode(n1);
			break;
		case 2:
			cout << "key and data" << endl;		//prepend
			cin >> key >> data;
			n1->setData(data);
			n1->setKey(key);
			node.prependNode(n1);
			break;
		case 3:
			cout << "삽입할 위치" << endl;		//insert
			cin >> key1;
			cout << "key and data" << endl;
			cin >> key >> data;
			n1->setData(data);
			n1->setKey(key);
			node.insertNode(key1, n1);
			break;
		case 4:
			cout << "제거할 노드의 key" << endl;	//delete
			cin >> key;
			node.deleteNode(key);
			break;
		case 5:
			cout << "업데이트할 key와 data" << endl;	//update
			cin >> key >> data;
			node.updateNode(key, data);
			break;
		case 6:
			node.printList();					//print
			break;
		case 7:
			system("cls");						//clear
			break;
		case 8:
			cout << "장비를 정지합니다";		//exit
			delete n1;				//동적할당된 노드 제거
			return 0;
		default:break;
		}
	}
}