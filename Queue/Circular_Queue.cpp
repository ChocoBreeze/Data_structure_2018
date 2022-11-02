#include<iostream>

const int MAX_STACK_SIZE = 100;
typedef int element;

struct QueueType {
	element queue[MAX_STACK_SIZE];
	int front, rear;
};

void init(QueueType *q) { //�ʱ�ȭ
	q->front = q->rear = 0;
}

int is_empty(QueueType *q) {	// front == rear �������
	return (q->front == q->rear);
}

int is_full(QueueType *q) {		// rear+1�� front�� ���� ť�� ũ��� ������ ������ ��ȭ����
	return ((q->rear + 1)%MAX_STACK_SIZE == (q->front) % MAX_STACK_SIZE);
}

void enqueue(QueueType *q, element item) {	//����
	if (is_full(q)) { std::cout << "Queue is full\n"; exit(1); }
	q->rear = (q->rear + 1) % MAX_STACK_SIZE;	// rear+1
	q->queue[q->rear] = item; // ����
}

element dequeue(QueueType *q) { //���� �� ��ȯ
	if (is_empty(q)) { std::cout << "Queue is empty\n"; exit(1); }
	q->front = (q->front + 1) % MAX_STACK_SIZE;	// front+1
	return q->queue[q->front]; // ��ȯ
}

element peek(QueueType *q) { // �������� ��ȯ
	if (is_empty(q)) { std::cout << "Queue is empty\n"; exit(1); }
	return q->queue[q->front+1];	// front���� ��ȭ x
}

void main() {
	QueueType q; // �����ͷ� �����ϸ� ������ �ʱ�ȭ x
	init(&q);
	std::cout << "front = " << q.front << " rear = " << q.rear << std::endl;
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	std::cout << "peek() = " << peek(&q) << std::endl;
	std::cout << "dequeue() = " << dequeue(&q) << std::endl;
	std::cout << "peek() = " << peek(&q) << std::endl;
	std::cout << "dequeue() = " << dequeue(&q) << std::endl;
	std::cout << "peek() = " << peek(&q) << std::endl;
	std::cout << "dequeue() = " << dequeue(&q) << std::endl;
	std::cout << "peek() = " << peek(&q) << std::endl;
	std::cout << "front = " << q.front << " rear = " << q.rear;
}