//수식의 계산
#include<iostream>

const int MAX_STACK_SIZE = 100;
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

int eval(char exp[]) {	// 후위 표기식이 입력된 경우
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;

	init(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0';	//입력이 피연산자이면 그냥 출력 
			push(&s, value);
		}
		else {	//연산자이면 피연산자를 스택에서 제거
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) { // 연산을 수행하고 스택에 저장
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
//연산자 우선순위 순서 ( < ) <  +,- < *,/
void infix_to_postfix(char exp[]) { // 중위 -> 후위
	int i = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;	// 연산자를 저장하는 스택

	init(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		//연산자이면
		switch (ch) {
		case '+':
		case '*':
		case '-':
		case '/':
			//스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) std::cout << (char)pop(&s);
			push(&s, ch);
			break;
		case '(': // 왼쪽 괄호
			push(&s, ch);
			break;
		case ')':	//오른쪽 괄호
			top_op = pop(&s); //왼쪽 괄호를 만날때까지 출력
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
	while (!is_empty(&s)) //스택에 저장된 연산자들 출력
		std::cout << (char)pop(&s);
}
int main()
{
	infix_to_postfix("(1+2)+7");
	std::cout << std::endl <<  eval("12+7+");
	return 0;
}