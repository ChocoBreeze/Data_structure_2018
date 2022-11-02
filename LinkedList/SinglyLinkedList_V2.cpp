#include<iostream>
#include<string>
using namespace std;


typedef int element;
struct ListNode {
	element data;
	ListNode* link;
};
struct LinkedListType { // ����Ʈ�� ���� ����ü
	ListNode *head;	// ��� ������
	int length;		// ����� ����
};

void insert_node(ListNode **phead, ListNode*p, ListNode *new_node) {
	// phead == �� �� �κ�, p == ���� �ڸ�, new_node = ���� ��
	// 1 phead ==NULL -> �� ����Ʈ�� ����
	// 2 p==NULL -> �� �տ� ����
	// 3 �Ϲ����� �߰� ���� p ������ ����
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
	// p��  removed ���� ��带 ����Ŵ.
	//1 p ==NULL �� �� ��� ����
	//2 p !=NULL �߰� ��� ����.
	if (p == NULL) {
		*phead = (*phead)->link;
	}
	else {
		p->link = removed->link;
	}
	delete removed;
}

void init(LinkedListType *list) { //����Ʈ �Լ� �ʱ�ȭ
	if (list == NULL) return;
	list->length = 0;
	list->head = NULL;

}

int is_empty(LinkedListType *list) { //���� ����Ʈ�̸� 1 ����
	if (list->head == NULL) return 1;
	else return 0;
}

int get_length(LinkedListType *list) { // ����Ʈ ���� ��ȯ
	return list->length;
}

ListNode *get_node_at(LinkedListType *list, int pos) { // �Ű� ���� pos�� �Է� �޾Ƽ� pos ��ġ�� ��带 ��ȯ
	// insert_node, remove_node�� �Բ� add, delete�� �����ϴ� �� ���
	ListNode *tmp_node = list->head;
	if (pos < 0) return NULL;
	for (int i = 0; i < pos; i++)
		tmp_node = tmp_node->link;
	return tmp_node;
}

void add(LinkedListType *list, int pos, element data) {
	ListNode *p;
	if ((pos >= 0) && (pos <= list->length)) { // ��ġ�� ���ռ� �˻�
		ListNode *node = new ListNode;
		node->data = data; // ������ ��忡 ������ �� ����
		p = get_node_at(list, pos - 1);	// ���� ��ġ �ٷ� �տ� ��ġ�� ��� ã��
		insert_node(&(list->head), p, node);	// ��� ����
		list->length++;		// ��ü ����Ʈ ũ�� ����
	}
	else
		cout << "���� ��ġ �߸� ����";
}

void add_last(LinkedListType *list, element data) {
	add(list, get_length(list), data);
}

void add_first(LinkedListType *list, element data) {
	add(list, 0, data);
}

void delete_node(LinkedListType *list, int pos) { //������ �ƴ� ����Ʈ���� pos ��ġ�� ������ ����
	if (list->length!=0 && (pos >= 0) && (pos < list->length)) { // ��ġ ���ռ� ���� ������ �� ���� !is_empty(list)��� ���Դµ� ��ȣ�ϴٰ� ���ͼ� ����.
		ListNode *p = get_node_at(list, pos - 1);
		remove_node(&(list->head), p, (p != NULL) ? p->link : NULL);
		list->length--;
	}
}

element get_entry(LinkedListType *list, int pos) { // pos ��ġ�� �����͸� ��ȯ
	ListNode *p;
	if (pos < 0 && pos >= list->length) cout << "��ġ ����";
	p = get_node_at(list, pos);
	return p->data;
}

void clear(LinkedListType *list) { // ��� ��带 ����
	for (int i = 0; i < list->length; i++) {
		delete_node(list, i);
	}
}

void display(LinkedListType *list) { // List ��ü ���
	ListNode *node = list->head;
	cout << "(";
	for (int i = 0; i < list->length; i++) {
		cout << node->data;
		node = node->link;
	}
	cout << ")\n";
}

int is_in_list(LinkedListType *list, element item) { // �ش� �����Ͱ� �����ϴ��� ���� ��ȯ
	ListNode *p;
	p = list->head; // ��� �����Ϳ��� ����
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

	string k= is_in_list(&list1, 20) == 1 ? "����" : "����";
	cout << k << endl;
	cout << get_entry(&list1, 0);

	return 0;

}