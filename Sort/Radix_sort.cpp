// radix sort 기수 정렬
#include<iostream>
const int MAX_SIZE = 100;
const int BUCKETS = 10;
const int DIGITS = 4;
struct QueueType {
	int queue[MAX_SIZE];
	int front, rear;
};

void init(QueueType *q) { //초기화
	q->front = q->rear = 0;
}

int is_empty(QueueType *q) {	// front == rear 공백상태
	return (q->front == q->rear);
}

int is_full(QueueType *q) {		// rear+1과 front를 각각 큐의 크기로 나눈게 같으면 포화상태
	return ((q->rear + 1) % MAX_SIZE == (q->front) % MAX_SIZE);
}

void enqueue(QueueType *q, int item) {	//삽입
	if (is_full(q)) { std::cout << "Queue is full\n"; exit(1); }
	q->rear = (q->rear + 1) % MAX_SIZE;	// rear+1
	q->queue[q->rear] = item; // 삽입
}

int dequeue(QueueType *q) { //삭제 후 반환
	if (is_empty(q)) { std::cout << "Queue is empty\n"; exit(1); }
	q->front = (q->front + 1) % MAX_SIZE;	// front+1
	return q->queue[q->front]; // 반환
}

void radix_sort(int list[], int n) {
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) init(&queues[b]);
	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++) { // 버켓에 자리 수별로 채움
			enqueue(&queues[(list[i] / factor) % 10], list[i]);
		}
		for (b = i = 0; b < BUCKETS; b++) { // 버켓의 데이터를 list로 옮김
			while (!is_empty(&queues[b])) list[i++] = dequeue(&queues[b]);
		}
		factor *= 10;
	}
}