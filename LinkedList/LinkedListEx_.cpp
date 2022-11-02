//���׽�
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

void init(ListHeader *plist) { // �ʱ�ȭ �Լ�
	plist->length = 0;
	plist->head = plist->tail = NULL;
}

//plist�� ���� ����Ʈ�� ����� ����Ű�� ������, coef�� ���, expon�� ����
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
	while (a&&b) { // �Ѵ� NULL�� �ƴ� �� �ݺ�
		if(a->expon ==b->expon) { // a�� ���� = b�� ����
			sum = a->coef + b->coef;
			if (sum != 0) insert_node_last(plist3, sum, a->expon);
			a = a->link; b = b->link;
		}
		else if (a->expon > b->expon) { // a�� ���� > b�� ����
			insert_node_last(plist3, a->coef, a->expon);
			a = a->link;
		}
		else {	// a�� ���� < b�� ����
			insert_node_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}
	// a�� b���� �ϳ��� ���� ������ �Ǹ� �����ִ� �׵��� ��� ��� ���׽����� ����
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

	//���� ����Ʈ�� �ʱ�ȭ
	init(&list1);
	init(&list2);
	init(&list3);
	//���׽� 1�� ����
	insert_node_last(&list1, 3, 12);
	insert_node_last(&list1, 2, 8);
	insert_node_last(&list1, 1, 0);
	//���׽� 2�� ����
	insert_node_last(&list2, 8, 12);
	insert_node_last(&list2, -3, 10);
	insert_node_last(&list2, 10, 6);
	poly_add(&list1, &list2, &list3);
	poly_print(&list3);
	clear(&list1);
	clear(&list2);
	clear(&list3);
}