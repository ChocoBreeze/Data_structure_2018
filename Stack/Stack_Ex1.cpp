// ��ȣ �˻�
#include<iostream>
#include<cstring>

const int MAX_STACK_SIZE = 100;
typedef char element;
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

int check_matching(char *in) {
	StackType s;
	char ch, open_ch;
	init(&s);
	int n = strlen(in);

	for (int i = 0; i < n; i++) {
		ch = in[i];
		switch (ch) {
		case '(':
		case '[':
		case '{':
			push(&s, ch);
			break;
		case ')':
		case ']':
		case '}':
			if (is_empty(&s)) return 0;
			else {
				open_ch = pop(&s);
				if (open_ch == '(' && ch != ')' || open_ch == '[' && ch != ']' || open_ch == '{' && ch != '}') return 0;
			}
			break;
		}
	}
	if (!is_empty(&s)) return 0;	//�� �����̸� return 1
	return 1;
}

int main()
{
	if (check_matching("{A[(i+1)]=0; }") == 1) std::cout << "��ȣ �˻� ����";
	else std::cout << "��ȣ �˻� ����";
	return 0;
}