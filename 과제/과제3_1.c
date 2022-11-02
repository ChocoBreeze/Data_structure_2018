/*
Student_info.txt
학번	이름(성, 이름) 의 형식으로 된 txt 파일
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100		// 학생 수 배열 크기
#define BUCKETS 10			// Radix sort를 하기 위한 BUCKETS=10
#define DIGITS 3			// Radix sort를 하기 위한 숫자의 자릿수

typedef struct STUDENTS {	// Student 구조체 선언
	char name[100];
	int student_number;
	int score;
} STUDENTS;

STUDENTS students[MAX_SIZE];	
int start;					// 시작 시간
double time_;				// 시간을 구하는 변수

//Selection sort 선택 정렬
void selection_sort(STUDENTS list[], int n) { // 선택 정렬
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

//Insertion sort 삽입 정렬
void insertion_sort(STUDENTS list[], int n) { 
	int i, j;
	STUDENTS key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j].score < key.score; j--) {
			list[j + 1] = list[j];
		}
		list[j + 1] = key;	// 적절한 위치에 삽입.
	}
}

//Bubble sort 버블 정렬
void bubble_sort(STUDENTS list[], int n) {
	STUDENTS temp;
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {	// 앞, 뒤 레코드 비교 --> 교체
			if (list[j].score < list[j + 1].score) {
				temp = list[j];
				list[j] = list[j+1];
				list[j + 1] = temp;
			}
		}
	}
}

//Shell sort 쉘 정렬
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

//merge sort 합병 정렬 -- 추가 저장공간 필요
STUDENTS sorted[MAX_SIZE+1];
void merge(STUDENTS list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	while (i <= mid && j <= right) { // 좌,우에 있는 값을 sorted에 넣기
		if (list[i].score >= list[j].score) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}
	// 남아있는 배열 처리
	if (i > mid) for (l = j; l <= right; l++) sorted[k++] = list[l];
	else for (l = i; l <= mid; l++) sorted[k++] = list[l];
	// 배열 sorted를 원래 배열에 복사
	for (l = left; l <= right; l++) list[l] = sorted[l];
}
void merge_sort(STUDENTS list[], int left, int right) { // 자르는 것만
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid); //왼쪽
		merge_sort(list, mid + 1, right); // 오른쪽
		merge(list, left, mid, right); // 다시 합치기
	}
}

// quick sort - 퀵 정렬
int partition(STUDENTS list[], int left, int right) {
	STUDENTS pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left]; // pivot은 가장 왼쪽 숫자라고 가정
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
	if (left < right) { // 개수가 1개 이상
		int q = partition(list, left, right); // pivot을 기준으로 2개로 분할 한후 재귀
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

// radix sort 기수 정렬
typedef struct QueueType {
	STUDENTS queue[MAX_SIZE];
	int front, rear;
}QueueType;

void init(QueueType *q) { //초기화
	q->front = q->rear = 0;
}

int is_empty(QueueType *q) {	// front == rear 공백상태
	return (q->front == q->rear);
}

int is_full(QueueType *q) {		// rear+1과 front를 각각 큐의 크기로 나눈게 같으면 포화상태
	return ((q->rear + 1) % MAX_SIZE == (q->front) % MAX_SIZE);
}

void enqueue(QueueType *q, STUDENTS item) {	//삽입
	if (is_full(q)) return;
	q->rear = (q->rear + 1) % MAX_SIZE;	// rear+1
	q->queue[q->rear] = item; // 삽입
}

STUDENTS dequeue(QueueType *q) { //삭제 후 반환
	if (is_empty(q)) { printf("Queue is empty\n"); exit(1); }
	q->front = (q->front + 1) % MAX_SIZE;	// front+1
	return q->queue[q->front]; // 반환
}

void radix_sort(STUDENTS list[], int n) {
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) init(&queues[b]);
	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++) { // 버켓에 자리 수별로 채움
			enqueue(&queues[9-((list[i].score / factor) % 10)], list[i]);
		}
		for (b = i = 0; b < BUCKETS; b++) { // 버켓의 데이터를 list로 옮김
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
		fscanf(fp, "%d\t%[^\n]s\n", &students[i].student_number, students[i].name);	// 입력 받음
	}
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		if(i!=99) printf("Time : %d\t",i);
		for (int j = 0; j < 100; j++) {
			students[j].score = rand() % 101;		// i값이 바뀔때마다 점수를 새로운 값으로 초기화
			temp_list[j] = students[j];				// 임시 배열인 temp_list에 값을 복사
		}
		start = clock();							// 시작 시간
		selection_sort(temp_list,MAX_SIZE);			// 정렬
		time_ = (double)(clock() - start) / 1000;	// 수행 시간
		sum[0] += time_;
		printf("SELECTION SORT : %.6lf ",time_);	// 시간 출력
		if (i == 99) {								// i=99일 때 정렬 결과를 출력한다
			for (int j = 0; j < 100; j++) {
				printf("\n%d %3d %20s",temp_list[j].student_number,temp_list[j].score,temp_list[j].name);
			}
			printf("\n");
		}

		for (int j = 0; j < 100; j++) {
			temp_list[j] = students[j];
		}
		start = clock();							// 시작 시간
		insertion_sort(temp_list, MAX_SIZE);		// 정렬
		time_ = (double)(clock() - start) / 1000;	// 수행 시간
		sum[1] += time_;
		printf("INSERTION SORT : %.6lf ",time_);	// 시간 출력
		if (i == 99) {								// i=99일 때 정렬 결과를 출력한다
			for (int j = 0; j < 100; j++) {
				printf("\n%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
			}
			printf("\n");
		}

		for (int j = 0; j < 100; j++) {
			temp_list[j] = students[j];
		}
		start = clock();							// 시작 시간
		bubble_sort(temp_list, MAX_SIZE);			// 정렬
		time_ = (double)(clock() - start) / 1000;	// 수행 시간
		sum[2] += time_;
		printf("BUBBLE SORT : %.6lf ", time_);		// 시간 출력
		if (i == 99) {								// i=99일 때 정렬 결과를 출력한다
			for (int j = 0; j < 100; j++) {
				printf("\n%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
			}
			printf("\n");
		}

		for (int j = 0; j < 100; j++) {
			temp_list[j] = students[j];
		}
		start = clock();							// 시작 시간
		insertion_sort(temp_list, MAX_SIZE);		// 정렬
		time_ = (double)(clock() - start) / 1000;	// 수행 시간
		sum[3] += time_;
		printf("SHELL SORT : %.6lf ", time_);		// 시간 출력
		if (i == 99) {								// i=99일 때 정렬 결과를 출력한다
			for (int j = 0; j < 100; j++) {
				printf("\n%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
			}
			printf("\n");
		}

		for (int j = 0; j < 100; j++) {
			temp_list[j] = students[j];
		}
		start = clock();							// 시작 시간
		merge_sort(temp_list, 0, MAX_SIZE);			// 정렬
		time_ = (double)(clock() - start) / 1000;	// 수행 시간
		sum[4] += time_;
		printf("MERGE SORT : %.6lf ", time_);		// 시간 출력
		if (i == 99) {								// i=99일 때 정렬 결과를 출력한다
			for (int j = 0; j < 100; j++) {
				printf("\n%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
			}
			printf("\n");
		}

		for (int j = 0; j < 100; j++) {
			temp_list[j] = students[j];
		}
		start = clock();							// 시작 시간
		quick_sort(temp_list, 0, MAX_SIZE);			// 정렬
		time_ = (double)(clock() - start) / 1000;	// 수행 시간
		sum[5] += time_;
		printf("QUICK SORT : %.6lf ", time_);		// 시간 출력
		if (i == 99) {								// i=99일 때 정렬 결과를 출력한다
			for (int j = 0; j < 100; j++) {
				printf("\n%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
			}
			printf("\n");
		}

		for (int j = 0; j < 100; j++) {
			temp_list[j] = students[j];
		}
		start = clock();							// 시작 시간
		radix_sort(temp_list, MAX_SIZE);			// 정렬
		time_ = (double)(clock() - start) / 1000;	// 수행 시간
		sum[6] += time_;
		printf("RADIX SORT : %.6lf \n", time_);		// 시간 출력
		if (i == 99) {								// i=99일 때 정렬 결과를 출력한다
			for (int j = 0; j < 100; j++) {
				if(j==0) printf("%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
				else printf("\n%d %3d %20s", temp_list[j].student_number, temp_list[j].score, temp_list[j].name);
			}
			printf("\n");
		}

	}
	for (int i = 0; i < 7; i++) {			//Selecetion sort, Insertion sort, Bubble sort, Shell sort, Merge sort, Quick sort, Radix sort
		printf("%.10lf\n",sum[i]/100);		//의 평균 시간을 차례대로 출력
	}
	return 0;
}