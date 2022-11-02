/**/
#include<iostream>

const int MAX_STACK_SIZE=100;
typedef int element;
struct StackType {
	element stack[MAX_STACK_SIZE];
	int top;
};

void init(StackType *s) { // 초기화
	s->top = -1;
}

int is_empty(StackType *s) { // 비어있다면 1을 반환
	return (s->top == -1);
}

int is_full(StackType *s) {	// MAX_STACK_SIZE개수가 있다면 1을 반환
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item) { // 맨 위에 넣기
	if (is_full(s)) {
		std::cout << "overflow\n";
		return;
	}
	else s->stack[++(s->top)] = item;
}

element pop(StackType *s) {	// 맨 위에 있던 값 빼기 + 삭제
	if (is_empty(s)) {
		std::cout << "underflow\n";
		exit(1);
	}
	else return s->stack[(s->top)--];
}

element peek(StackType *s) { // 맨 위에 있던 값 빼기
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