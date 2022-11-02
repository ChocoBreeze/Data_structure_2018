#include<iostream>

typedef int element;

struct StackNode {
	element item;
	struct StackNode *link;
};
struct LinkedStackType {
	StackNode *top;
};

void init(LinkedStackType *s) { // 초기화
	s->top = NULL;
}

int is_empty(LinkedStackType *s) { // 비어있다면 1을 반환
	return (s->top == NULL);
}

void push(LinkedStackType *s, element item) { // 새로운 데이터 꼭대기에 넣기
	StackNode *temp = new StackNode;
	temp->item = item;
	temp->link = s->top;	// 새로운 노드(temp)를 top를 가리키게 함
	s->top = temp;			// top이 temp를 가리키게 함.
} 

element pop(LinkedStackType *s) { // 맨 위에 데이터 삭제 후 반환
	if (is_empty(s)) {
		std::cout << "empty stack\n";
		exit(1);
	}
	else {
		StackNode *temp = s->top;
		element item = temp->item;
		s->top = s->top->link;	// top을 (top-1)위치의 노드를 가리키게 함
		delete temp;			// top이 가리키는 노드의 동적 메모리 해제
		return item;
	}
}

element peek(LinkedStackType *s) { // 맨 위에 데이터 반환
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