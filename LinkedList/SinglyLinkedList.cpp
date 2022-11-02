#include<iostream>
using namespace std;
// typedef int element;
using element = int;
struct ListNode {
	element data;
	ListNode* link;
};

//노드 생성 함수
ListNode* create_node(element data, ListNode * link)
{
	ListNode* newnode = new ListNode;
	newnode->data = data;
	newnode->link = link;
	return newnode;
}

// 노드 삽입 함수
void insert_node(ListNode **phead, ListNode*p, ListNode *new_node)
{
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

//removed 노드를 지우는 함수.
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
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

//출력 함수
void display_node(ListNode* head)
{
	ListNode *p = head;
	while (p != NULL) {
		cout << p->data;
		p = p->link;
	}
	cout << endl;
}

//검색 함수
ListNode *search(ListNode *head, int x)
{
	ListNode *p;
	p = head;
	while (p != NULL) {
		if (p->data == x) return p; // 탐색 성공
		p = p->link;
	}
	return p; // 탐색 실패시 NULL 반환
}

//합병 함수
ListNode *concat(ListNode *head1, ListNode *head2)
{
	// 1뒤에 2를 연결
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;
	else
	{
		ListNode *p;
		p = head1;
		while (p->link != NULL)
			p = p->link;
		p->link = head2;
		return head1;
	}
}

//역순으로 만드는 함수
ListNode *reverse(ListNode *head)
{
	// 순회 포인터로 p, q, r을 사용
	ListNode *p, *q, *r;
	p = head;	//p는 역순으로 만들 리스트
	q = NULL;	//q는 역순으로 만들 노드
	while (p != NULL) {
		r = q;	//r은 역순으로 된 리스트
		q = p;	//현재 역순으로 만들 노드
		p = p->link;	//다음으로 역순으로 만들 노드
		q->link = r;	//q의 링크 방향을 바꾼다.
	}
	return q; // q는 역순으로 된 리스트의 헤드 포인터
}
int main()
{
	ListNode *list1 = NULL, *list2 = NULL;
	ListNode *p;
	insert_node(&list1, NULL, create_node(10, NULL));
	insert_node(&list1, NULL, create_node(20, NULL));
	insert_node(&list1, NULL, create_node(30, NULL));
	display_node(list1);

	remove_node(&list1, NULL, list1);
	display_node(list1);

	insert_node(&list2, NULL, create_node(60, NULL));
	insert_node(&list2, NULL, create_node(70, NULL));
	insert_node(&list2, NULL, create_node(80, NULL));
	display_node(list2);

	list1 = concat(list1, list2);
	display_node(list1);

	list1 = reverse(list1);
	display_node(list1);

	p = search(list1, 20);
	if (p == NULL) cout << "탐색 실패\n";
	else cout << "탐색 성공 : " << p->data << endl;

	return 0;
}