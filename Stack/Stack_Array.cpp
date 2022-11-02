/**/
#include<iostream>

const int MAX_STACK_SIZE=100;
typedef int element;
struct StackType {
	element stack[MAX_STACK_SIZE];
	int top;
};

void init(StackType *s) { // �ʱ�ȭ
	s->top = -1;
}

int is_empty(StackType *s) { // ����ִٸ� 1�� ��ȯ
	return (s->top == -1);
}

int is_full(StackType *s) {	// MAX_STACK_SIZE������ �ִٸ� 1�� ��ȯ
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item) { // �� ���� �ֱ�
	if (is_full(s)) {
		std::cout << "overflow\n";
		return;
	}
	else s->stack[++(s->top)] = item;
}

element pop(StackType *s) {	// �� ���� �ִ� �� ���� + ����
	if (is_empty(s)) {
		std::cout << "underflow\n";
		exit(1);
	}
	else return s->stack[(s->top)--];
}

element peek(StackType *s) { // �� ���� �ִ� �� ����
	if (is_empty(s)) {
		std::cout << "underflow\n";
		exit(1);
	}
	else return s->stack[(s->top)];
}

int main()
{
	StackType s;
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