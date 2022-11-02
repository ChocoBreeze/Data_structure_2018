/*
Student_info.txt
�й�	�̸�(��, �̸�) �� �������� �� txt ����
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct student {
	char name[100];		// �̸�
	int student_number;	// �й�
	int score;			// ����
} student;

typedef struct student_list {
	student s;
	struct student_list *llink, *rlink;
}student_list;

void init(student_list *node) {	// ���߿��Ḯ��Ʈ �ʱ�ȭ
	node->llink = node->rlink = node;
}

void dinsert_node(student_list *head_node, student *new_data) {
	student_list *new_node = (student_list*)malloc(sizeof(student_list)); // �޸� �Ҵ�
	new_node->s.score = rand() % 101; // ���� ����
	strcpy_s(new_node->s.name, sizeof(new_node->s.name), new_data->name); // �̸� ����
	new_node->s.student_number = new_data->student_number; // �й� ����
	student_list *search=head_node;
	if (head_node->rlink != head_node) { // head_node�� �����ϴ� ��찡 �ƴ� ��
		for (search = head_node->rlink; search != head_node; search=search->rlink) { // head_node���� ����ؼ� �ٽ� head_node�� ���ƿ� �� ���� �ݺ��ϸ鼭 �˸��� ��ġ(before ���)�� ã��.
			if (search->s.score < new_node->s.score) break; // �� ��庸�� ���� ���� ��带 ã�� ���
		}
	}
	 search = search->llink; // ã�� ��ġ�� before��带 ã�� ���� �������� �� �� �̵� 
	new_node->llink = search;
	new_node->rlink = search->rlink;
	search->rlink->llink = new_node;
	search->rlink = new_node;				// before����� search�� new_node�� after��带 ����.
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
		fscanf_s(fp, "%d\t%[^\n]s\n", &tmp.student_number, tmp.name, sizeof(tmp.name)); // �Է� ����
		dinsert_node(&head_node, &tmp); // ��� ����
	}
	printf("���� 10��\n");
	printf("�̸� \t\t     �й� \t ����\n");
	student_list* tmp1 = head_node.rlink;
	for (int i = 0; i < 10; i++) {
		printf("%-20s %-11d %-3d\n",tmp1->s.name,tmp1->s.student_number, tmp1->s.score);
		tmp1 = tmp1->rlink; // ������ ���� �̵�
	}
	printf("\n\n���� 10��\n");
	printf("�̸� \t\t     �й� \t ����\n");
	tmp1 = head_node.llink;
	for (int i = 0; i < 10; i++) {
		printf("%-20s %-11d %-3d\n", tmp1->s.name, tmp1->s.student_number, tmp1->s.score);
		tmp1 = tmp1->llink; // ���� ���� �̵�
	}
	return 0;
}
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct student {
	char name[100];		// �̸�
	int student_number;	// �й�
	int score;			// ����
} student;

typedef struct student_list {
	student s;
	struct student_list *llink, *rlink;
}student_list;

void init(student_list *node) {	// ���߿��Ḯ��Ʈ �ʱ�ȭ
	node->llink = node->rlink = node;
}

void dinsert_node(student_list *head_node, student *new_data) {
	student_list *new_node = (student_list*)malloc(sizeof(student_list)); // �޸� �Ҵ�
	new_node->s.score = rand() % 101; // ���� ����
	strcpy_s(new_node->s.name, sizeof(new_node->s.name), new_data->name); // �̸� ����
	new_node->s.student_number = new_data->student_number; // �й� ����
	student_list *search = head_node;
	if (head_node->rlink != head_node) { // head_node�� �����ϴ� ��찡 �ƴ� ��
		for (search = head_node->rlink; search != head_node; search = search->rlink) { // head_node���� ����ؼ� �ٽ� head_node�� ���ƿ� �� ���� �ݺ��ϸ鼭 �˸��� ��ġ(before ���)�� ã��.
			if (search->s.score < new_node->s.score) break; // �� ��庸�� ���� ���� ��带 ã�� ���
		}
	}
	search = search->llink; // ã�� ��ġ�� before��带 ã�� ���� �������� �� �� �̵� 
	new_node->llink = search;
	new_node->rlink = search->rlink;
	search->rlink->llink = new_node;
	search->rlink = new_node;				// before����� search�� new_node�� after��带 ����.
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
		fscanf_s(fp, "%d\t%[^\n]s\n", &tmp.student_number, tmp.name, sizeof(tmp.name)); // �Է� ����
		dinsert_node(&head_node, &tmp); // ��� ����
	}
	printf("���� 10��\n");
	printf("�̸� \t\t     �й� \t ����\n");
	student_list* tmp1 = head_node.rlink;
	for (int i = 0; i < 10; i++) {
		printf("%-20s %-11d %-3d\n", tmp1->s.name, tmp1->s.student_number, tmp1->s.score);
		tmp1 = tmp1->rlink; // ������ ���� �̵�
	}
	printf("\n\n���� 10��\n");
	printf("�̸� \t\t     �й� \t ����\n");
	tmp1 = head_node.llink;
	for (int i = 0; i < 10; i++) {
		printf("%-20s %-11d %-3d\n", tmp1->s.name, tmp1->s.student_number, tmp1->s.score);
		tmp1 = tmp1->llink; // ���� ���� �̵�
	}
	return 0;
}