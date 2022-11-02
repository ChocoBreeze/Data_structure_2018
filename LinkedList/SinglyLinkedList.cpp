#include<iostream>
using namespace std;
// typedef int element;
using element = int;
struct ListNode {
	element data;
	ListNode* link;
};

//��� ���� �Լ�
ListNode* create_node(element data, ListNode * link)
{
	ListNode* newnode = new ListNode;
	newnode->data = data;
	newnode->link = link;
	return newnode;
}

// ��� ���� �Լ�
void insert_node(ListNode **phead, ListNode*p, ListNode *new_node)
{
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

//removed ��带 ����� �Լ�.
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
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

//��� �Լ�
void display_node(ListNode* head)
{
	ListNode *p = head;
	while (p != NULL) {
		cout << p->data;
		p = p->link;
	}
	cout << endl;
}

//�˻� �Լ�
ListNode *search(ListNode *head, int x)
{
	ListNode *p;
	p = head;
	while (p != NULL) {
		if (p->data == x) return p; // Ž�� ����
		p = p->link;
	}
	return p; // Ž�� ���н� NULL ��ȯ
}

//�պ� �Լ�
ListNode *concat(ListNode *head1, ListNode *head2)
{
	// 1�ڿ� 2�� ����
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

//�������� ����� �Լ�
ListNode *reverse(ListNode *head)
{
	// ��ȸ �����ͷ� p, q, r�� ���
	ListNode *p, *q, *r;
	p = head;	//p�� �������� ���� ����Ʈ
	q = NULL;	//q�� �������� ���� ���
	while (p != NULL) {
		r = q;	//r�� �������� �� ����Ʈ
		q = p;	//���� �������� ���� ���
		p = p->link;	//�������� �������� ���� ���
		q->link = r;	//q�� ��ũ ������ �ٲ۴�.
	}
	return q; // q�� �������� �� ����Ʈ�� ��� ������
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
	if (p == NULL) cout << "Ž�� ����\n";
	else cout << "Ž�� ���� : " << p->data << endl;

	return 0;
}