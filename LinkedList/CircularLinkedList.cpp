#include<iostream>

typedef int element;
struct ListNode {
	element data;
	ListNode *link;
};

ListNode *create_node(element data, ListNode *link) {
	ListNode *new_node;
	new_node = new ListNode;
	new_node->data = data;
	new_node->link = link;
	return new_node;
}

void insert_first(ListNode ** phead, ListNode *node) {
	// phead ???? ?? ???? ??? (??? ??? ???)
	// node ??? ??
	if (*phead == NULL) {
		*phead = node;
		node->link = node;
	}
	else {
		node->link = (*phead)->link;	// node->next? ??? ??((*phead)->next)? ????
		(*phead)->link = node;			// ??? ??? next? node? ????
	}
}

void insert_last(ListNode **phead, ListNode *node) {
	// phead ???? ?? ???? ??? (??? ??? ???)
	// node ??? ??
	if (*phead == NULL) {
		*phead = node;
		node->link = node;
	}
	else {
		node->link = (*phead)->link;	// node->next? ??? ??((*phead)->next)? ????
		(*phead)->link = node;			// ??? ??? next? node? ????
		*phead = node;					// ?? ???? ??? node? ??
	}
}

void display(ListNode * head) {
	ListNode *p;
	if (head == NULL) return;

	p = head;
	do {
		printf("%d->",p->data);
		p = p->link;
	} while (p != head);
}

void clear(ListNode *head) {
	ListNode *p;
	if (head == NULL) return;

	p = head;
	do {
		ListNode *k;
		k = p;
		p = p->link;
		delete k;
	} while (p != head);
}

int main()
{
	ListNode *list1 = NULL;
	insert_first(&list1, create_node(10, NULL));
	insert_first(&list1, create_node(20, NULL));
	insert_last(&list1, create_node(30, NULL));
	display(list1);
	clear(list1);
	return 0;
}