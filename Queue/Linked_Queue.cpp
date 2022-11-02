#include<iostream>
typedef int element;
struct QueueNode{	// queue의 노드
	element item;
	QueueNode* link;
};

struct QueueType {	//queue를 위한 구조체
	QueueNode *front, *rear;
};

void init(QueueType *q) { // 초기화
	q->front = q->rear = NULL;
}

int is_empty(QueueType *q) {
	return(q->front == NULL);
}

void enqueue(QueueType *q, element item) { // 삽입
	QueueNode* temp = new QueueNode;
	temp->item = item;
	temp->link = NULL;
	if (is_empty(q)) { // queue가 공백 상태 --> front와 rear가 새로운 노드를 가리키게 함
		q->front = q->rear= temp;
	}
	else { // 기존 노드가 있는 경우
		q->rear->link = temp;	// rear의 링크를 새로운 노드로
		q->rear = temp;	// rear를 새로운 노드를 가르키도록
	}
}
element dequeue(QueueType *q) { // 삭제 후 반환
	if (is_empty(q)) { std::cout << "queue is empty"; exit(1); }
	QueueNode *temp = q->front; // front의 노드를 temp가 가리키게 함
	element item;
	item = temp->item;
	q->front = q->front->link; // front 값 이동
	if (q->front == NULL) q->rear = NULL; // front가 NULL이면 rear도 NULL로
	delete temp; // temp의 메모리 해제
	return item;
}
element peek(QueueType *q) { // 반환
	if (is_empty(q)) { std::cout << "queue is empty"; exit(1); }
	return q->front->item;
}

int main()
{
	QueueType q;
	init(&q);
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