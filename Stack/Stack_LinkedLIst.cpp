#include<iostream>

typedef int element;

struct StackNode {
	element item;
	struct StackNode *link;
};
struct LinkedStackType {
	StackNode *top;
};

void init(LinkedStackType *s) { // �ʱ�ȭ
	s->top = NULL;
}

int is_empty(LinkedStackType *s) { // ����ִٸ� 1�� ��ȯ
	return (s->top == NULL);
}

void push(LinkedStackType *s, element item) { // ���ο� ������ ����⿡ �ֱ�
	StackNode *temp = new StackNode;
	temp->item = item;
	temp->link = s->top;	// ���ο� ���(temp)�� top�� ����Ű�� ��
	s->top = temp;			// top�� temp�� ����Ű�� ��.
} 

element pop(LinkedStackType *s) { // �� ���� ������ ���� �� ��ȯ
	if (is_empty(s)) {
		std::cout << "empty stack\n";
		exit(1);
	}
	else {
		StackNode *temp = s->top;
		element item = temp->item;
		s->top = s->top->link;	// top�� (top-1)��ġ�� ��带 ����Ű�� ��
		delete temp;			// top�� ����Ű�� ����� ���� �޸� ����
		return item;
	}
}

element peek(LinkedStackType *s) { // �� ���� ������ ��ȯ
	if (is_empty(s)) {
		std::cout << "empty stack\n";
		exit(1);
	}
	else {
		return s->top->item;
	}
}

int main()
{
	LinkedStackType s;
	init(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	std::cout << peek(&s) << std::endl;
	std::cout << pop(&s) << std::endl;
	std::cout << pop(&s) << std::endl;
	std::cout << pop(&s) << std::endl;
	std::cout << is_empty(&s);
	return 0;
}