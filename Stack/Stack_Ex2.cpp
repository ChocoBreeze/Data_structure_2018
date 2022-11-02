//������ ���
#include<iostream>

const int MAX_STACK_SIZE = 100;
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

int eval(char exp[]) {	// ���� ǥ����� �Էµ� ���
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;

	init(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0';	//�Է��� �ǿ������̸� �׳� ��� 
			push(&s, value);
		}
		else {	//�������̸� �ǿ����ڸ� ���ÿ��� ����
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) { // ������ �����ϰ� ���ÿ� ����
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;

			}
		}
	}
	return pop(&s);
}

int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
}
//������ �켱���� ���� ( < ) <  +,- < *,/
void infix_to_postfix(char exp[]) { // ���� -> ����
	int i = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;	// �����ڸ� �����ϴ� ����

	init(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		//�������̸�
		switch (ch) {
		case '+':
		case '*':
		case '-':
		case '/':
			//���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) std::cout << (char)pop(&s);
			push(&s, ch);
			break;
		case '(': // ���� ��ȣ
			push(&s, ch);
			break;
		case ')':	//������ ��ȣ
			top_op = pop(&s); //���� ��ȣ�� ���������� ���
			while (top_op != '(') {
				std::cout << (char)top_op;
				top_op = pop(&s);
			}
			break;
		default:
			std::cout << (char)ch;
			break;
		}
	}
	while (!is_empty(&s)) //���ÿ� ����� �����ڵ� ���
		std::cout << (char)pop(&s);
}
int main()
{
	infix_to_postfix("(1+2)+7");
	std::cout << std::endl <<  eval("12+7+");
	return 0;
}