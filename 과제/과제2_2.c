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

path_stack ps_print;		// 결과 출력용 스택
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
}; // 지도 초기화

void init(path_stack *ps) { // 스택 초기화
	ps->top = NULL;
}

int is_empty(path_stack *ps) { // 빈 스택인지 확인
	return (ps->top == NULL);
}

int push(path_stack *ps, int x, int y) {	// 0이면 실패 1이면 성공
	path_stack *ps1 = &ps_print;
	path *print_top;
	for (print_top = ps1->top; print_top != NULL; print_top = print_top->link) { // 중복 검사
		if (print_top->e.x == x && print_top->e.y == y) return 0;
	}
	path *new_path = (path*)malloc(sizeof(path));
	new_path->e.x = x;
	new_path->e.y = y;
	new_path->link = ps->top;
	ps->top = new_path;					// 갈 수 있는 경로에 new_path의 좌표값을 추가
	if(ps!=&ps_print) printf("push : (%d , %d)\n",new_path->e.x,new_path->e.y);
	return 1;
}

 element pop(path_stack *ps) { 
	 if (is_empty(ps)) { printf("빈 스택"); exit(1); }
	 else {
		 path *tmp = ps->top;
		 element tmp_e = ps->top->e;
		 ps->top = ps->top->link;
		 free(tmp);
		 return(tmp_e);
	 }
 }
 void pop_select(path_stack *ps,element k) {	// 특정한 k와 인접한 값을 찾을때까지 삭제
	 element tmp; 
	 while(1) {
		 tmp = pop(ps);
		 if (ps->top) {
			 if (ps->top->e.x + 1 == k.x && ps->top->e.y == k.y) break; // 원하는 k의 위
			 if (ps->top->e.x - 1 == k.x && ps->top->e.y == k.y) break; // 원하는 k의 아래
			 if (ps->top->e.x == k.x && ps->top->e.y + 1 == k.y) break;	// 원하는 k의 왼쪽
			 if (ps->top->e.x == k.x && ps->top->e.y - 1 == k.y) break;	// 원하는 k의 오른쪽
		 }
	 }
 }

void find_path(path_stack *ps) { // 경로 탐색
	element tmp;
	int chk,chk1; // chk는 push의 성공여부를 ch1는 갈 수 있는 길이 있는지 확인
	while (1)
	{
		tmp = pop(ps);			// top의 위치를 pop
		push(&ps_print, tmp.x, tmp.y);	// print용 스택에 방금 꺼낸 위치를 push
		printf("pop : (%d , %d)\n", tmp.x, tmp.y);
		if (tmp.x == 8 && tmp.y == 9) break; // 도착이니 스탑
		chk = 0; chk1 = 0;
		if (map[tmp.x + 1][tmp.y] == 0 && tmp.x < 9) { chk1 = push(ps, tmp.x + 1, tmp.y); if (chk1 == 1) chk = 1; chk1 = 0; }	// 아래
		if (map[tmp.x - 1][tmp.y] == 0 && tmp.x > 0) { chk1 = push(ps, tmp.x - 1, tmp.y); if (chk1 == 1) chk = 1; chk1 = 0; }	// 위
		if (map[tmp.x][tmp.y - 1] == 0 && tmp.y > 0) { chk1 = push(ps, tmp.x, tmp.y - 1); if (chk1 == 1) chk = 1; chk1 = 0; }	// 왼쪽
		if (map[tmp.x][tmp.y + 1] == 0 && tmp.y < 9) { chk1 = push(ps, tmp.x, tmp.y + 1); if (chk1 == 1) chk = 1; chk1 = 0; }   // 오른쪽
	//	if (chk == 0) { // 갈 수 있는 길이 없기 때문에 print용 스택에서 원하는 값에 인접한 값이 나올때까지 그 과정에 나오는 모든 값들을 삭제
		//	pop_select(&ps_print, ps->top->e);
	//	}
	}
}

void print_stack(path *ps) {		// 스택 출력
	if (ps->link != NULL) {
		print_stack(ps->link);
	}
	printf("(%d , %d) -> ",ps->e.x,ps->e.y);
}
int main()
{
	path_stack ps;		// 갈 수 있는 경로를 쌓는 스택
	init(&ps);
	init(&ps_print);
	push(&ps, 1, 0);
	find_path(&ps);
	printf("총 경로 : \n");
	print_stack(ps_print.top);
	printf("도착\n");
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int element;

typedef struct pos {
	int x;
	int y;

}pos; // 현재위치를 저장하는 구조체

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

} // pos 구조체의 값을 받아서 스택에 push 한다

pos pop(LinkedStackType *s) {

	StackNode *temp = s->top;
	pos item = temp->item;
	s->top = s->top->link;
	free(temp);
	return item;
}
LinkedStackType FS; // 스택에서 pop한 결과를 저장하는 스택 FS를 선언
void found(pos *s, int(*p)[10], LinkedStackType *t)
{
	pos temp;
	int a = s->x;
	int b = s->y; // 현재 위치 값을 임시적으로 a,b에 저장

	if (a == 8 && b == 9) {
		return;
	} // 출구를 만나면 빠져나옴

	else {

		p[a][b] = 1;
		if (a < 9 && p[a + 1][b] != 1) {
			s->x = a + 1;
			push(t, s);
			printf("push : (%d, %d)\n", s->x, s->y);

			s->x = a;

		} // 아래쪽 위치를 검사해서 뚫린길이면 스택에 push 한다
		if (a > 0 && p[a - 1][b] != 1) {
			s->x = a - 1;
			push(t, s);
			printf("push : (%d, %d)\n", s->x, s->y);
			s->x = a;

		}// 위쪽 위치를 검사해서 뚫린길이면 스택에 push 한다
		if (b > 0 && p[a][b - 1] != 1) {
			s->y = b - 1;
			push(t, s);
			printf("push : (%d, %d)\n", s->x, s->y);
			s->y = b;

		}// 왼쪽 위치를 검사해서 뚫린길이면 스택에 push 한다
		if (b < 9 && p[a][b + 1] != 1) {
			s->y = b + 1;
			push(t, s);
			printf("push : (%d, %d)\n", s->x, s->y);
			s->y = b;

		}// 아래 위치를 검사해서 뚫린길이면 스택에 push 한다
		temp = pop(t);
		s = &temp;
		push(&FS, &temp); // pop한 값을 결과용 스택FS에 push 한다.
		printf("pop : (%d, %d)\n", s->x, s->y);
		found(s, p, t); // 재귀를 돌림

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
	}; // 미로 배열선언

	int(*p)[10] = arr;
	LinkedStackType t, FA;
	init(&FA);
	init(&t);
	pos st;
	st.x = 1; //출발점 선언
	st.y = 0; //출발점 선언
	push(&FS, &st);  // 출발점을 결과용 스택에 넣음
	found(&st, p, &t); // 재귀를 돌림

	pos tempp; // 결과용 스택을 출발점부터 꺼내기 위해 이용하는 pos값


	while (FS.top != NULL) {
		tempp = pop(&FS);
		push(&FA, &tempp);
	} // FS 라는 결과용 스택을 출발점부터 꺼내기 위해 다시 POP해서 FA라는 스택에 PUSH함 

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
} // 최종 스택인 FA 에서 top이 NULL이 될때 까지 출력