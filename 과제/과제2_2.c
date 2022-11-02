#include<stdio.h>
#include<stdlib.h>

typedef struct element {
	int x;
	int y;
} element;
typedef struct path {
	element e;
	struct path *link;
} path;

typedef struct path_stack {
	struct path *top;
}path_stack;				

path_stack ps_print;		// ��� ��¿� ����
int map[10][10] = {
	{ 1,1,1,1,1,1,1,1,1,1 }
	,{ 0,0,0,0,1,0,0,0,0,1 }
	,{ 1,0,0,0,1,0,0,0,0,1 }
	,{ 1,0,1,1,1,0,0,1,0,1 }
	,{ 1,0,0,0,1,0,0,1,0,1 }
	,{ 1,0,1,0,1,0,0,1,0,1 }
	,{ 1,0,1,0,1,0,0,1,0,1 }
	,{ 1,0,1,0,1,0,0,1,0,1 }
	,{ 1,0,1,0,0,0,0,1,0,0 }
	,{ 1,1,1,1,1,1,1,1,1,1 }
}; // ���� �ʱ�ȭ

void init(path_stack *ps) { // ���� �ʱ�ȭ
	ps->top = NULL;
}

int is_empty(path_stack *ps) { // �� �������� Ȯ��
	return (ps->top == NULL);
}

int push(path_stack *ps, int x, int y) {	// 0�̸� ���� 1�̸� ����
	path_stack *ps1 = &ps_print;
	path *print_top;
	for (print_top = ps1->top; print_top != NULL; print_top = print_top->link) { // �ߺ� �˻�
		if (print_top->e.x == x && print_top->e.y == y) return 0;
	}
	path *new_path = (path*)malloc(sizeof(path));
	new_path->e.x = x;
	new_path->e.y = y;
	new_path->link = ps->top;
	ps->top = new_path;					// �� �� �ִ� ��ο� new_path�� ��ǥ���� �߰�
	if(ps!=&ps_print) printf("push : (%d , %d)\n",new_path->e.x,new_path->e.y);
	return 1;
}

 element pop(path_stack *ps) { 
	 if (is_empty(ps)) { printf("�� ����"); exit(1); }
	 else {
		 path *tmp = ps->top;
		 element tmp_e = ps->top->e;
		 ps->top = ps->top->link;
		 free(tmp);
		 return(tmp_e);
	 }
 }
 void pop_select(path_stack *ps,element k) {	// Ư���� k�� ������ ���� ã�������� ����
	 element tmp; 
	 while(1) {
		 tmp = pop(ps);
		 if (ps->top) {
			 if (ps->top->e.x + 1 == k.x && ps->top->e.y == k.y) break; // ���ϴ� k�� ��
			 if (ps->top->e.x - 1 == k.x && ps->top->e.y == k.y) break; // ���ϴ� k�� �Ʒ�
			 if (ps->top->e.x == k.x && ps->top->e.y + 1 == k.y) break;	// ���ϴ� k�� ����
			 if (ps->top->e.x == k.x && ps->top->e.y - 1 == k.y) break;	// ���ϴ� k�� ������
		 }
	 }
 }

void find_path(path_stack *ps) { // ��� Ž��
	element tmp;
	int chk,chk1; // chk�� push�� �������θ� ch1�� �� �� �ִ� ���� �ִ��� Ȯ��
	while (1)
	{
		tmp = pop(ps);			// top�� ��ġ�� pop
		push(&ps_print, tmp.x, tmp.y);	// print�� ���ÿ� ��� ���� ��ġ�� push
		printf("pop : (%d , %d)\n", tmp.x, tmp.y);
		if (tmp.x == 8 && tmp.y == 9) break; // �����̴� ��ž
		chk = 0; chk1 = 0;
		if (map[tmp.x + 1][tmp.y] == 0 && tmp.x < 9) { chk1 = push(ps, tmp.x + 1, tmp.y); if (chk1 == 1) chk = 1; chk1 = 0; }	// �Ʒ�
		if (map[tmp.x - 1][tmp.y] == 0 && tmp.x > 0) { chk1 = push(ps, tmp.x - 1, tmp.y); if (chk1 == 1) chk = 1; chk1 = 0; }	// ��
		if (map[tmp.x][tmp.y - 1] == 0 && tmp.y > 0) { chk1 = push(ps, tmp.x, tmp.y - 1); if (chk1 == 1) chk = 1; chk1 = 0; }	// ����
		if (map[tmp.x][tmp.y + 1] == 0 && tmp.y < 9) { chk1 = push(ps, tmp.x, tmp.y + 1); if (chk1 == 1) chk = 1; chk1 = 0; }   // ������
	//	if (chk == 0) { // �� �� �ִ� ���� ���� ������ print�� ���ÿ��� ���ϴ� ���� ������ ���� ���ö����� �� ������ ������ ��� ������ ����
		//	pop_select(&ps_print, ps->top->e);
	//	}
	}
}

void print_stack(path *ps) {		// ���� ���
	if (ps->link != NULL) {
		print_stack(ps->link);
	}
	printf("(%d , %d) -> ",ps->e.x,ps->e.y);
}
int main()
{
	path_stack ps;		// �� �� �ִ� ��θ� �״� ����
	init(&ps);
	init(&ps_print);
	push(&ps, 1, 0);
	find_path(&ps);
	printf("�� ��� : \n");
	print_stack(ps_print.top);
	printf("����\n");
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int element;

typedef struct pos {
	int x;
	int y;

}pos; // ������ġ�� �����ϴ� ����ü

typedef struct StackNode {
	pos item;
	struct StackNode *link;
} StackNode;

typedef struct {
	StackNode *top;
} LinkedStackType;

void init(LinkedStackType *s) {

	s->top = NULL;
}

void push(LinkedStackType *s, pos *item) {
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	temp->item.x = item->x;
	temp->item.y = item->y;
	temp->link = s->top;
	s->top = temp;

} // pos ����ü�� ���� �޾Ƽ� ���ÿ� push �Ѵ�

pos pop(LinkedStackType *s) {

	StackNode *temp = s->top;
	pos item = temp->item;
	s->top = s->top->link;
	free(temp);
	return item;
}
LinkedStackType FS; // ���ÿ��� pop�� ����� �����ϴ� ���� FS�� ����
void found(pos *s, int(*p)[10], LinkedStackType *t)
{
	pos temp;
	int a = s->x;
	int b = s->y; // ���� ��ġ ���� �ӽ������� a,b�� ����

	if (a == 8 && b == 9) {
		return;
	} // �ⱸ�� ������ ��������

	else {

		p[a][b] = 1;
		if (a < 9 && p[a + 1][b] != 1) {
			s->x = a + 1;
			push(t, s);
			printf("push : (%d, %d)\n", s->x, s->y);

			s->x = a;

		} // �Ʒ��� ��ġ�� �˻��ؼ� �ո����̸� ���ÿ� push �Ѵ�
		if (a > 0 && p[a - 1][b] != 1) {
			s->x = a - 1;
			push(t, s);
			printf("push : (%d, %d)\n", s->x, s->y);
			s->x = a;

		}// ���� ��ġ�� �˻��ؼ� �ո����̸� ���ÿ� push �Ѵ�
		if (b > 0 && p[a][b - 1] != 1) {
			s->y = b - 1;
			push(t, s);
			printf("push : (%d, %d)\n", s->x, s->y);
			s->y = b;

		}// ���� ��ġ�� �˻��ؼ� �ո����̸� ���ÿ� push �Ѵ�
		if (b < 9 && p[a][b + 1] != 1) {
			s->y = b + 1;
			push(t, s);
			printf("push : (%d, %d)\n", s->x, s->y);
			s->y = b;

		}// �Ʒ� ��ġ�� �˻��ؼ� �ո����̸� ���ÿ� push �Ѵ�
		temp = pop(t);
		s = &temp;
		push(&FS, &temp); // pop�� ���� ����� ����FS�� push �Ѵ�.
		printf("pop : (%d, %d)\n", s->x, s->y);
		found(s, p, t); // ��͸� ����

	}
}

int main() {

	int arr[10][10] = {
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 0,0,0,0,1,0,0,0,0,1 },
		{ 1,0,0,0,1,0,0,0,0,1 },
		{ 1,0,1,1,1,0,0,1,0,1 },
		{ 1,0,0,0,1,0,0,1,0,1 },
		{ 1,0,1,0,1,0,0,1,0,1 },
		{ 1,0,1,0,1,0,0,1,0,1 },
		{ 1,0,1,0,1,0,0,1,0,1 },
		{ 1,0,1,0,0,0,0,1,0,0 },
		{ 1,1,1,1,1,1,1,1,1,1 }
	}; // �̷� �迭����

	int(*p)[10] = arr;
	LinkedStackType t, FA;
	init(&FA);
	init(&t);
	pos st;
	st.x = 1; //����� ����
	st.y = 0; //����� ����
	push(&FS, &st);  // ������� ����� ���ÿ� ����
	found(&st, p, &t); // ��͸� ����

	pos tempp; // ����� ������ ��������� ������ ���� �̿��ϴ� pos��


	while (FS.top != NULL) {
		tempp = pop(&FS);
		push(&FA, &tempp);
	} // FS ��� ����� ������ ��������� ������ ���� �ٽ� POP�ؼ� FA��� ���ÿ� PUSH�� 

	printf("\n");

	while (FA.top != NULL) {

		tempp = pop(&FA);
		if (tempp.x == 8 && tempp.y == 9) {
			printf("(%d, %d)", tempp.x, tempp.y);
		}
		else {
			printf("(%d, %d) -> ", tempp.x, tempp.y);
		}
	}
} // ���� ������ FA ���� top�� NULL�� �ɶ� ���� ���