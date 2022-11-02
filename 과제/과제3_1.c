/*
Student_info.txt
�й�	�̸�(��, �̸�) �� �������� �� txt ����
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100		// �л� �� �迭 ũ��
#define BUCKETS 10			// Radix sort�� �ϱ� ���� BUCKETS=10
#define DIGITS 3			// Radix sort�� �ϱ� ���� ������ �ڸ���

typedef struct STUDENTS {	// Student ����ü ����
	char name[100];
	int student_number;
	int score;
} STUDENTS;

STUDENTS students[MAX_SIZE];	
int start;					// ���� �ð�
double time_;				// �ð��� ���ϴ� ����

//Selection sort ���� ����
void selection_sort(STUDENTS list[], int n) { // ���� ����
	int least;
	STUDENTS temp;
	for (int i = 0; i < n - 1; i++) {
		least = i;
		for (int j = i + 1; j < n; j++) {
			if (list[j].score > list[least].score) least = j;
		}
		if (i != least) {
			temp = list[i];
			list[i] = list[least];
			list[least] = temp;
		}
	}
}

//Insertion sort ���� ����
void insertion_sort(STUDENTS list[], int n) { 
	int i, j;
	STUDENTS key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j].score < key.score; j--) {
			list[j + 1] = list[j];
		}
		list[j + 1] = key;	// ������ ��ġ�� ����.
	}
}

//Bubble sort ���� ����
void bubble_sort(STUDENTS list[], int n) {
	STUDENTS temp;
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {	// ��, �� ���ڵ� �� --> ��ü
			if (list[j].score < list[j + 1].score) {
				temp = list[j];
				list[j] = list[j+1];
				list[j + 1] = temp;
			}
		}
	}
}

//Shell sort �� ����
void inc_insertion_sort(STUDENTS list[], int first, int last, int gap) {
	int i, j;
	STUDENTS key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key.score > list[j].score; j = j - gap) {
			list[j + gap] = list[j];
		}
		list[j + gap] = key;
	}
}
void shell_sort(STUDENTS list[], int n) {
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if (gap % 2 == 0) gap++;
		for (i = 0; i < gap; i++) {
			inc_insertion_sort(list, i, n - 1, gap);
		}
	}
}

//merge sort �պ� ���� -- �߰� ������� �ʿ�
STUDENTS sorted[MAX_SIZE+1];
void merge(STUDENTS list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	while (i <= mid && j <= right) { // ��,�쿡 �ִ� ���� sorted�� �ֱ�
		if (list[i].score >= list[j].score) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}
	// �����ִ� �迭 ó��
	if (i > mid) for (l = j; l <= right; l++) sorted[k++] = list[l];
	else for (l = i; l <= mid; l++) sorted[k++] = list[l];
	// �迭 sorted�� ���� �迭�� ����
	for (l = left; l <= right; l++) list[l] = sorted[l];
}
void merge_sort(STUDENTS list[], int left, int right) { // �ڸ��� �͸�
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid); //����
		merge_sort(list, mid + 1, right); // ������
		merge(list, left, mid, right); // �ٽ� ��ġ��
	}
}

// quick sort - �� ����
int partition(STUDENTS list[], int left, int right) {
	STUDENTS pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left]; // pivot�� ���� ���� ���ڶ�� ����
	do {
		do {
			low++;
		} while (low <= right && list[low].score > pivot.score);
		do {
			high--;
		} while (high >= left && list[high].score < pivot.score);
		if (low < high) {
			temp = list[low];
			list[low] = list[high];
			list[high] = temp;
		}
	} while (low < high);
	temp = list[left];
	list[left] = list[high];
	list[high] = temp;
	return high;
}

void quick_sort(STUDENTS list[], int left, int right) {
	if (left < right) { // ������ 1�� �̻�
		int q = partition(list, left, right); // pivot�� �������� 2���� ���� ���� ���
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

// radix sort ��� ����
typedef struct QueueType {
	STUDENTS queue[MAX_SIZE];
	int front, rear;
}QueueType;

void init(QueueType *q) { //�ʱ�ȭ
	q->front = q->rear = 0;
}

int is_empty(QueueType *q) {	// front == rear �������
	return (q->front == q->rear);
}

int is_full(QueueType *q) {		// rear+1�� front�� ���� ť�� ũ��� ������ ������ ��ȭ����
	return ((q->rear + 1) % MAX_SIZE == (q->front) % MAX_SIZE);
}

void enqueue(QueueType *q, STUDENTS item) {	//����
	if (is_full(q)) return;
	q->rear = (q->rear + 1) % MAX_SIZE;	// rear+1
	q->queue[q->rear] = item; // ����
}

STUDENTS dequeue(QueueType *q) { //���� �� ��ȯ
	if (is_empty(q)) { printf("Queue is empty\n"); exit(1); }
	q->front = (q->front + 1) % MAX_SIZE;	// front+1
	return q->queue[q->front]; // ��ȯ
}

void radix_sort(STUDENTS list[], int n) {
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) init(&queues[b]);
	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++) { // ���Ͽ� �ڸ� ������ ä��
			enqueue(&queues[9-((list[i].score / factor) % 10)], list[i]);
		}
		for (b = i = 0; b < BUCKETS; b++) { // ������ �����͸� list�� �ű�
			while (!is_empty(&queues[b])) list[i++] = dequeue(&queues[b]);
		}
		factor *= 10;
	}
}

int main()
{
	STUDENTS temp_list[MAX_SIZE+1];
	double sum[7] = { 0, };
	FILE* fp = fopen("Student_info.txt", "r");
	if (fp == NULL) exit(1);
	for (int i = 0; i < MAX_SIZE; i++) {
		fscanf(fp, "%d\t%[^\n]s\n", &students[i].student_number, students[i].name);	// �Է� ����
	}
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		if(i!=99) printf("Time : %d\t",i);
		for (int j = 0; j < 100; j++) {
			students[j].score = rand() % 101;		// i���� �ٲ𶧸��� ������ ���ο� ������ �ʱ�ȭ
			temp_list[j] = students[j];				// �ӽ� �迭�� temp_list�� ���� ����
		}
		start = clock();							// ���� �ð�
		selection_sort(temp_list,MAX_SIZE);			// ����
		time_ = (double)(clock() - start) / 1000;	// ���� �ð�
		sum[0] += time_;
		printf("SELECTION SORT : %.6lf ",time_);	// �ð� ���
		if (i == 99) {								// i=99�� �� ���� ����� ����Ѵ�
			for (int j = 0; j < 100; j++) {
				printf("\n%d %3d %20s",temp_list[j].student_number,temp_list[j].score,temp_list[j].name);
			}
			printf("\n");
		}

		for (int j = 0; j < 100; j++) {
			temp_list[j] = students[j];
		}
		start = clock();							// ���� �ð�
		insertion_sort(temp_list, MAX_SIZE);		// ����
		time_ = (double)(clock() - start) / 1000;	// ���� �ð�
		sum[1] += time_;
		printf("INSERTION SORT : %.6lf ",time_);	// �ð� ���
		if (i == 99) {								// i=99�� �� ���� ����� ����Ѵ�
			for (int j = 0; j < 100; j++) {
				printf("\n%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
			}
			printf("\n");
		}

		for (int j = 0; j < 100; j++) {
			temp_list[j] = students[j];
		}
		start = clock();							// ���� �ð�
		bubble_sort(temp_list, MAX_SIZE);			// ����
		time_ = (double)(clock() - start) / 1000;	// ���� �ð�
		sum[2] += time_;
		printf("BUBBLE SORT : %.6lf ", time_);		// �ð� ���
		if (i == 99) {								// i=99�� �� ���� ����� ����Ѵ�
			for (int j = 0; j < 100; j++) {
				printf("\n%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
			}
			printf("\n");
		}

		for (int j = 0; j < 100; j++) {
			temp_list[j] = students[j];
		}
		start = clock();							// ���� �ð�
		insertion_sort(temp_list, MAX_SIZE);		// ����
		time_ = (double)(clock() - start) / 1000;	// ���� �ð�
		sum[3] += time_;
		printf("SHELL SORT : %.6lf ", time_);		// �ð� ���
		if (i == 99) {								// i=99�� �� ���� ����� ����Ѵ�
			for (int j = 0; j < 100; j++) {
				printf("\n%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
			}
			printf("\n");
		}

		for (int j = 0; j < 100; j++) {
			temp_list[j] = students[j];
		}
		start = clock();							// ���� �ð�
		merge_sort(temp_list, 0, MAX_SIZE);			// ����
		time_ = (double)(clock() - start) / 1000;	// ���� �ð�
		sum[4] += time_;
		printf("MERGE SORT : %.6lf ", time_);		// �ð� ���
		if (i == 99) {								// i=99�� �� ���� ����� ����Ѵ�
			for (int j = 0; j < 100; j++) {
				printf("\n%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
			}
			printf("\n");
		}

		for (int j = 0; j < 100; j++) {
			temp_list[j] = students[j];
		}
		start = clock();							// ���� �ð�
		quick_sort(temp_list, 0, MAX_SIZE);			// ����
		time_ = (double)(clock() - start) / 1000;	// ���� �ð�
		sum[5] += time_;
		printf("QUICK SORT : %.6lf ", time_);		// �ð� ���
		if (i == 99) {								// i=99�� �� ���� ����� ����Ѵ�
			for (int j = 0; j < 100; j++) {
				printf("\n%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
			}
			printf("\n");
		}

		for (int j = 0; j < 100; j++) {
			temp_list[j] = students[j];
		}
		start = clock();							// ���� �ð�
		radix_sort(temp_list, MAX_SIZE);			// ����
		time_ = (double)(clock() - start) / 1000;	// ���� �ð�
		sum[6] += time_;
		printf("RADIX SORT : %.6lf \n", time_);		// �ð� ���
		if (i == 99) {								// i=99�� �� ���� ����� ����Ѵ�
			for (int j = 0; j < 100; j++) {
				if(j==0) printf("%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
				else printf("\n%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
			}
			printf("\n");
		}

	}
	for (int i = 0; i < 7; i++) {			//Selecetion sort, Insertion sort, Bubble sort, Shell sort, Merge sort, Quick sort, Radix sort
		printf("%.10lf\n",sum[i]/100);		//�� ��� �ð��� ���ʴ�� ���
	}
	return 0;
}