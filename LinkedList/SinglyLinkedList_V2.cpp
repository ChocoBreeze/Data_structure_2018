#include<iostream>
#include<string>
using namespace std;


typedef int element;
struct ListNode {
	element data;
	ListNode* link;
};
struct LinkedListType { // 리스트를 위한 구조체
	ListNode *head;	// 헤드 포인터
	int length;		// 노드의 개수
};

void insert_node(ListNode **phead, ListNode*p, ListNode *new_node) {
	// phead == 맨 앞 부분, p == 넣을 자리, new_node = 넣을 것
	// 1 phead ==NULL -> 빈 리스트에 삽입
	// 2 p==NULL -> 맨 앞에 삽입
	// 3 일반적인 중간 삽입 p 다음에 삽입
	if (phead == NULL) {
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) {
		new_node->link = *phead;
		*phead = new_node;
	}
	else {
		new_node->link = p->link;
		p->link = new_node;
	}
}

void remove_node(ListNode **phead, ListNode *p, ListNode *removed) {
	// p는  removed 앞의 노드를 가리킴.
	//1 p ==NULL 맨 앞 노드 삭제
	//2 p !=NULL 중간 노드 삭제.
	if (p == NULL) {
		*phead = (*phead)->link;
	}
	else {
		p->link = removed->link;
	}
	delete removed;
}

void init(LinkedListType *list) { //리스트 함수 초기화
	if (list == NULL) return;
	list->length = 0;
	list->head = NULL;

}

int is_empty(LinkedListType *list) { //공백 리스트이면 1 리턴
	if (list->head == NULL) return 1;
	else return 0;
}

int get_length(LinkedListType *list) { // 리스트 개수 반환
	return list->length;
}

ListNode *get_node_at(LinkedListType *list, int pos) { // 매개 변수 pos를 입력 받아서 pos 위치의 노드를 반환
	// insert_node, remove_node와 함께 add, delete를 구현하는 데 사용
	ListNode *tmp_node = list->head;
	if (pos < 0) return NULL;
	for (int i = 0; i < pos; i++)
		tmp_node = tmp_node->link;
	return tmp_node;
}

void add(LinkedListType *list, int pos, element data) {
	ListNode *p;
	if ((pos >= 0) && (pos <= list->length)) { // 위치의 적합성 검사
		ListNode *node = new ListNode;
		node->data = data; // 삽입할 노드에 데이터 값 저장
		p = get_node_at(list, pos - 1);	// 삽입 위치 바로 앞에 위치한 노드 찾기
		insert_node(&(list->head), p, node);	// 노드 삽입
		list->length++;		// 전체 리스트 크기 증가
	}
	else
		cout << "삽입 위치 잘못 지정";
}

void add_last(LinkedListType *list, element data) {
	add(list, get_length(list), data);
}

void add_first(LinkedListType *list, element data) {
	add(list, 0, data);
}

void delete_node(LinkedListType *list, int pos) { //공백이 아닌 리스트에서 pos 위치의 데이터 삭제
	if (list->length!=0 && (pos >= 0) && (pos < list->length)) { // 위치 적합성 조사 원래는 맨 앞이 !is_empty(list)라고 나왔는데 모호하다고 나와서 지움.
		ListNode *p = get_node_at(list, pos - 1);
		remove_node(&(list->head), p, (p != NULL) ? p->link : NULL);
		list->length--;
	}
}

element get_entry(LinkedListType *list, int pos) { // pos 위치의 데이터를 반환
	ListNode *p;
	if (pos < 0 && pos >= list->length) cout << "위치 오류";
	p = get_node_at(list, pos);
	return p->data;
}

void clear(LinkedListType *list) { // 모든 노드를 삭제
	for (int i = 0; i < list->length; i++) {
		delete_node(list, i);
	}
}

void display(LinkedListType *list) { // List 전체 출력
	ListNode *node = list->head;
	cout << "(";
	for (int i = 0; i < list->length; i++) {
		cout << node->data;
		node = node->link;
	}
	cout << ")\n";
}

int is_in_list(LinkedListType *list, element item) { // 해당 데이터가 존재하는지 여부 반환
	ListNode *p;
	p = list->head; // 헤드 포인터에서 시작
	while (p != NULL) {
		if (p->data == item) break;
		p = p->link;
	}
	if (p == NULL) return 0;
	else return 1;
}

int main()
{
	LinkedListType list1;
	init(&list1);
	add(&list1, 0, 20);
	add_last(&list1, 30);
	add_first(&list1, 10);
	add_last(&list1, 40);

	display(&list1);

	delete_node(&list1, 3);
	display(&list1);

	delete_node(&list1, 0);
	display(&list1);

	string k= is_in_list(&list1, 20) == 1 ? "성공" : "실패";
	cout << k << endl;
	cout << get_entry(&list1, 0);

	return 0;

}