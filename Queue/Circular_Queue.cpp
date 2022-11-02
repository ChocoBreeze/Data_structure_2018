#include<iostream>

const int MAX_STACK_SIZE = 100;
typedef int element;

struct QueueType {
	element queue[MAX_STACK_SIZE];
	int front, rear;
};

void init(QueueType *q) { //초기화
	q->front = q->rear = 0;
}

int is_empty(QueueType *q) {	// front == rear 공백상태
	return (q->front == q->rear);
}

int is_full(QueueType *q) {		// rear+1과 front를 각각 큐의 크기로 나눈게 같으면 포화상태
	return ((q->rear + 1)%MAX_STACK_SIZE == (q->front) % MAX_STACK_SIZE);
}

void enqueue(QueueType *q, element item) {	//삽입
	if (is_full(q)) { std::cout << "Queue is full\n"; exit(1); }
	q->rear = (q->rear + 1) % MAX_STACK_SIZE;	// rear+1
	q->queue[q->rear] = item; // 삽입
}

element dequeue(QueueType *q) { //삭제 후 반환
	if (is_empty(q)) { std::cout << "Queue is empty\n"; exit(1); }
	q->front = (q->front + 1) % MAX_STACK_SIZE;	// front+1
	return q->queue[q->front]; // 반환
}

element peek(QueueType *q) { // 삭제없이 반환
	if (is_empty(q)) { std::cout << "Queue is empty\n"; exit(1); }
	return q->queue[q->front+1];	// front값의 변화 x
}

void main() {
	QueueType q; // 포인터로 선언하면 에러남 초기화 x
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