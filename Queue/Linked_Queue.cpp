#include<iostream>
typedef int element;
struct QueueNode{	// queue�� ���
	element item;
	QueueNode* link;
};

struct QueueType {	//queue�� ���� ����ü
	QueueNode *front, *rear;
};

void init(QueueType *q) { // �ʱ�ȭ
	q->front = q->rear = NULL;
}

int is_empty(QueueType *q) {
	return(q->front == NULL);
}

void enqueue(QueueType *q, element item) { // ����
	QueueNode* temp = new QueueNode;
	temp->item = item;
	temp->link = NULL;
	if (is_empty(q)) { // queue�� ���� ���� --> front�� rear�� ���ο� ��带 ����Ű�� ��
		q->front = q->rear= temp;
	}
	else { // ���� ��尡 �ִ� ���
		q->rear->link = temp;	// rear�� ��ũ�� ���ο� ����
		q->rear = temp;	// rear�� ���ο� ��带 ����Ű����
	}
}
element dequeue(QueueType *q) { // ���� �� ��ȯ
	if (is_empty(q)) { std::cout << "queue is empty"; exit(1); }
	QueueNode *temp = q->front; // front�� ��带 temp�� ����Ű�� ��
	element item;
	item = temp->item;
	q->front = q->front->link; // front �� �̵�
	if (q->front == NULL) q->rear = NULL; // front�� NULL�̸� rear�� NULL��
	delete temp; // temp�� �޸� ����
	return item;
}
element peek(QueueType *q) { // ��ȯ
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