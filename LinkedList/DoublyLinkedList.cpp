#include<iostream>

typedef int element;
struct DListNode {
	element data;
	struct DListNode *llink;
	struct DListNode *rlink;
};

void init(DListNode *phead) { //???
	phead->llink = phead;
	phead->rlink = phead;
}

void dinsert_node(DListNode *before, DListNode *new_node) {
	new_node->llink = before;				// new_node? llink? before? ???? ?
	new_node->rlink = before->rlink;		// new_node? rlink? after(before->rlink)? ???? ?
	before->rlink->llink = new_node;		// after_node? link? new_node? ????	?
	before->rlink = new_node;				// before??? rlink? new_node? ???? ?
}

void dremove_node(DListNode *phead_node, DListNode *removed) {
	if (removed == phead_node) return;
	removed->llink->rlink = removed->rlink;		// before ??? rlink(removed->llink->rlink)? after ??(removed->rlink)? ???? ?
	removed->rlink->llink = removed->llink;		// after ??? llink(removed->rlink->llink)? before ??(removed->llink)? ???? ?
	delete removed;								// removed ??? ??? ?? ??
}

void display(DListNode *phead) {
	DListNode *p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		std::cout << p->llink << "   " << p->data << "   " << p->rlink << std::endl;
	}
	std::cout << std::endl;
}

void clear(DListNode *phead) {
	DListNode *p,*k;
	p = phead->rlink;
	while (1) {
		if (p == phead) break;
		k = p;
		p = p->rlink;
		delete k;
	}
}
void main() {
	DListNode head_node;
	DListNode *p[10];
	int i;

	init(&head_node);
	for (i = 0; i < 5; i++) {
		p[i] = new DListNode;
		p[i]->data = i;	
		// ?? ??? ???? ??
		dinsert_node(&head_node, p[i]);
	}
	dremove_node(&head_node, p[4]);
	display(&head_node);
	clear(&head_node);
}