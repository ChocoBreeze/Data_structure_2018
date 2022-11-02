//다항식
#include<iostream>

struct ListNode {
	int coef;
	int expon;
	ListNode *link;
};

struct ListHeader {
	int length;
	ListNode* head;
	ListNode* tail;
};

void init(ListHeader *plist) { // 초기화 함수
	plist->length = 0;
	plist->head = plist->tail = NULL;
}

//plist는 연결 리스트의 헤더를 가리키는 포인터, coef는 계수, expon는 지수
void insert_node_last(ListHeader *plist, int coef, int expon) {
	ListNode *temp = new ListNode;
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->length++;
}

void poly_add(ListHeader *plist1, ListHeader* plist2, ListHeader* plist3) {
	ListNode *a = plist1->head;
	ListNode *b = plist2->head;
	int sum;
	while (a&&b) { // 둘다 NULL이 아닐 때 반복
		if(a->expon ==b->expon) { // a의 차수 = b의 차수
			sum = a->coef + b->coef;
			if (sum != 0) insert_node_last(plist3, sum, a->expon);
			a = a->link; b = b->link;
		}
		else if (a->expon > b->expon) { // a의 차수 > b의 차수
			insert_node_last(plist3, a->coef, a->expon);
			a = a->link;
		}
		else {	// a의 차수 < b의 차수
			insert_node_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}
	// a와 b중의 하나가 먼저 끝나게 되면 남아있는 항들을 모두 결과 다항식으로 복사
	for (; a != NULL; a = a->link) {
		insert_node_last(plist3, a->coef, a->expon);
	}
	for (; b != NULL; b = b->link) {
		insert_node_last(plist3, b->coef, b->expon);
	}
}

void poly_print(ListHeader* plist) {
	ListNode* p = plist->head;
	for (; p ; p = p->link) {
		std::cout << p->coef << " " << p->expon << std::endl;
	}
}

void clear(ListHeader *plist) {
	ListNode* p = plist->head;
	while (p != NULL) {
		ListNode* k = p;
		p = p->link;
		delete k;
	}
}
void main()
{
	ListHeader list1, list2, list3;

	//연결 리스트의 초기화
	init(&list1);
	init(&list2);
	init(&list3);
	//다항식 1을 생성
	insert_node_last(&list1, 3, 12);
	insert_node_last(&list1, 2, 8);
	insert_node_last(&list1, 1, 0);
	//다항식 2를 생성
	insert_node_last(&list2, 8, 12);
	insert_node_last(&list2, -3, 10);
	insert_node_last(&list2, 10, 6);
	poly_add(&list1, &list2, &list3);
	poly_print(&list3);
	clear(&list1);
	clear(&list2);
	clear(&list3);
}