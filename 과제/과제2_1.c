/*
Student_info.txt
학번	이름(성, 이름) 의 형식으로 된 txt 파일
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct student {
	char name[100];		// 이름
	int student_number;	// 학번
	int score;			// 점수
} student;

typedef struct student_list {
	student s;
	struct student_list *llink, *rlink;
}student_list;

void init(student_list *node) {	// 이중연결리스트 초기화
	node->llink = node->rlink = node;
}

void dinsert_node(student_list *head_node, student *new_data) {
	student_list *new_node = (student_list*)malloc(sizeof(student_list)); // 메모리 할당
	new_node->s.score = rand() % 101; // 점수 지정
	strcpy_s(new_node->s.name, sizeof(new_node->s.name), new_data->name); // 이름 복사
	new_node->s.student_number = new_data->student_number; // 학번 복사
	student_list *search=head_node;
	if (head_node->rlink != head_node) { // head_node만 존재하는 경우가 아닐 때
		for (search = head_node->rlink; search != head_node; search=search->rlink) { // head_node에서 출발해서 다시 head_node로 돌아올 때 까지 반복하면서 알맞은 위치(before 노드)를 찾음.
			if (search->s.score < new_node->s.score) break; // 새 노드보다 값이 작은 노드를 찾을 경우
		}
	}
	 search = search->llink; // 찾은 위치를 before노드를 찾기 위해 왼쪽으로 한 번 이동 
	new_node->llink = search;
	new_node->rlink = search->rlink;
	search->rlink->llink = new_node;
	search->rlink = new_node;				// before노드인 search와 new_node와 after노드를 연결.
}

int main()
{
	student_list head_node;
	student tmp;
	srand(time(NULL));
	init(&head_node);
	FILE*fp = fopen("student_info.txt", "r");
	if (fp == NULL) exit(1);
	for (int i = 0; i<100; i++) {
		fscanf_s(fp, "%d\t%[^\n]s\n", &tmp.student_number, tmp.name, sizeof(tmp.name)); // 입력 받음
		dinsert_node(&head_node, &tmp); // 노드 삽입
	}
	printf("상위 10명\n");
	printf("이름 \t\t     학번 \t 점수\n");
	student_list* tmp1 = head_node.rlink;
	for (int i = 0; i < 10; i++) {
		printf("%-20s %-11d %-3d\n",tmp1->s.name,tmp1->s.student_number, tmp1->s.score);
		tmp1 = tmp1->rlink; // 오른쪽 노드로 이동
	}
	printf("\n\n하위 10명\n");
	printf("이름 \t\t     학번 \t 점수\n");
	tmp1 = head_node.llink;
	for (int i = 0; i < 10; i++) {
		printf("%-20s %-11d %-3d\n", tmp1->s.name, tmp1->s.student_number, tmp1->s.score);
		tmp1 = tmp1->llink; // 왼쪽 노드로 이동
	}
	return 0;
}
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct student {
	char name[100];		// 이름
	int student_number;	// 학번
	int score;			// 점수
} student;

typedef struct student_list {
	student s;
	struct student_list *llink, *rlink;
}student_list;

void init(student_list *node) {	// 이중연결리스트 초기화
	node->llink = node->rlink = node;
}

void dinsert_node(student_list *head_node, student *new_data) {
	student_list *new_node = (student_list*)malloc(sizeof(student_list)); // 메모리 할당
	new_node->s.score = rand() % 101; // 점수 지정
	strcpy_s(new_node->s.name, sizeof(new_node->s.name), new_data->name); // 이름 복사
	new_node->s.student_number = new_data->student_number; // 학번 복사
	student_list *search = head_node;
	if (head_node->rlink != head_node) { // head_node만 존재하는 경우가 아닐 때
		for (search = head_node->rlink; search != head_node; search = search->rlink) { // head_node에서 출발해서 다시 head_node로 돌아올 때 까지 반복하면서 알맞은 위치(before 노드)를 찾음.
			if (search->s.score < new_node->s.score) break; // 새 노드보다 값이 작은 노드를 찾을 경우
		}
	}
	search = search->llink; // 찾은 위치를 before노드를 찾기 위해 왼쪽으로 한 번 이동 
	new_node->llink = search;
	new_node->rlink = search->rlink;
	search->rlink->llink = new_node;
	search->rlink = new_node;				// before노드인 search와 new_node와 after노드를 연결.
}

int main()
{
	student_list head_node;
	student tmp;
	srand(time(NULL));
	init(&head_node);
	FILE*fp = fopen("Student_info.txt", "r");
	if (fp == NULL) exit(1);
	for (int i = 0; i<100; i++) {
		fscanf_s(fp, "%d\t%[^\n]s\n", &tmp.student_number, tmp.name, sizeof(tmp.name)); // 입력 받음
		dinsert_node(&head_node, &tmp); // 노드 삽입
	}
	printf("상위 10명\n");
	printf("이름 \t\t     학번 \t 점수\n");
	student_list* tmp1 = head_node.rlink;
	for (int i = 0; i < 10; i++) {
		printf("%-20s %-11d %-3d\n", tmp1->s.name, tmp1->s.student_number, tmp1->s.score);
		tmp1 = tmp1->rlink; // 오른쪽 노드로 이동
	}
	printf("\n\n하위 10명\n");
	printf("이름 \t\t     학번 \t 점수\n");
	tmp1 = head_node.llink;
	for (int i = 0; i < 10; i++) {
		printf("%-20s %-11d %-3d\n", tmp1->s.name, tmp1->s.student_number, tmp1->s.score);
		tmp1 = tmp1->llink; // 왼쪽 노드로 이동
	}
	return 0;
}