// radix sort ��� ����
#include<iostream>
const int MAX_SIZE = 100;
const int BUCKETS = 10;
const int DIGITS = 4;
struct QueueType {
	int queue[MAX_SIZE];
	int front, rear;
};

void init(QueueType *q) { //�ʱ�ȭ
	q->front = q->rear = 0;
}

int is_empty(QueueType *q) {	// front == rear �������
	return (q->front == q->rear);
}

int is_full(QueueType *q) {		// rear+1�� front�� ���� ť�� ũ��� ������ ������ ��ȭ����
	return ((q->rear + 1) % MAX_SIZE == (q->front) % MAX_SIZE);
}

void enqueue(QueueType *q, int item) {	//����
	if (is_full(q)) { std::cout << "Queue is full\n"; exit(1); }
	q->rear = (q->rear + 1) % MAX_SIZE;	// rear+1
	q->queue[q->rear] = item; // ����
}

int dequeue(QueueType *q) { //���� �� ��ȯ
	if (is_empty(q)) { std::cout << "Queue is empty\n"; exit(1); }
	q->front = (q->front + 1) % MAX_SIZE;	// front+1
	return q->queue[q->front]; // ��ȯ
}

void radix_sort(int list[], int n) {
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) init(&queues[b]);
	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++) { // ���Ͽ� �ڸ� ������ ä��
			enqueue(&queues[(list[i] / factor) % 10], list[i]);
		}
		for (b = i = 0; b < BUCKETS; b++) { // ������ �����͸� list�� �ű�
			while (!is_empty(&queues[b])) list[i++] = dequeue(&queues[b]);
		}
		factor *= 10;
	}
}