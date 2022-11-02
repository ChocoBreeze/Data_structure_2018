// ���� ���� ���� ������ ť -- ���� ���� ����Ʈ ���
#include<iostream>

typedef int element;

struct DlistNode {
	element data;
	DlistNode* llink;
	DlistNode* rlink;
};

struct DequeType {
	DlistNode* head;
	DlistNode* tail;
};

void init(DequeType *dq) {
	dq->head = dq->tail = NULL;
}

int is_empty(DequeType *dq) {
	return(dq->head == NULL);
}

DlistNode *create_node(DlistNode *llink, element item, DlistNode *rlink) {
	DlistNode *node = new DlistNode;
	node->llink = llink;
	node->data = item;
	node->rlink = rlink;
	return node;
}

void add_rear(DequeType *dq, element item) {
	DlistNode* new_node = create_node(dq->tail, item, NULL);	// new_node�� llink�� tail�� ����Ű�� ��带 ����Ű�� ��

	if (is_empty(dq)) dq->head = new_node;
	else dq->tail->rlink = new_node;	// tail�� ����Ű�� node�� rlink�� new_node�� ����Ű�� ��
	dq->tail = new_node;		// tail�� new_node�� ����Ű�� ��
}

void add_front(DequeType *dq, element item) { 
	DlistNode* new_node = create_node(NULL, item, dq->head);	// new_node�� rlink�� head�� ����Ű�� ��带 ����Ű�� ��

	if (is_empty(dq)) dq->tail = new_node;
	else dq->head->llink = new_node;	// head�� ����Ű�� node�� llink�� new_node�� ����Ű�� ��
	dq->head = new_node;		// tail�� new_node�� ����Ű�� ��
}

element delete_front(DequeType *dq) {
	element item;
	DlistNode* removed_node;

	if (is_empty(dq)) { std::cout << "error"; exit(1); }
	else {
		removed_node = dq->head;
		item = removed_node->data;
		dq->head = dq->head->rlink;	// ��� ����
		delete removed_node;
		if (dq->head == NULL) dq->tail = NULL;
		else dq->head->llink = NULL;
	}
	return item;
}

element delete_rear(DequeType *dq) {
	element item;
	DlistNode *removed_node;

	if (is_empty(dq)) { std::cout << "error"; exit(1); }
	else {
		removed_node = dq->tail;
		item = removed_node->data;
		dq->tail = dq->tail->llink;	// tail ����
		delete removed_node;	// ������ ��� �޸� ����

		if (dq->tail == NULL) dq->head = NULL;
		else dq->tail->rlink = NULL;	// ����� rlink�� NULL��
	}
	return item;
}

void display(DequeType *dq) {
	DlistNode *p;
	std::cout << "( ";
	for(p=dq->head;p!=NULL;p=p->rlink){
		std::cout << p->data << " ";
	}
	std::cout << ")\n";
}

int main()
{
	DequeType deque;

	init(&deque);
	add_front(&deque, 10);
	add_front(&deque, 20);
	add_rear(&deque, 30);
	display(&deque);

	delete_front(&deque);
	delete_rear(&deque);
	display(&deque);
	delete_rear(&deque);
	display(&deque);
	return 0;
}