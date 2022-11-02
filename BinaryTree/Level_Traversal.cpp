/*
						+
					  *   / 
					A  B C  D
*/
#include<iostream>

struct TreeNode {
	char data;
	TreeNode *left, *right;
};

typedef TreeNode * element;
TreeNode n1 = { 'A',NULL,NULL };
TreeNode n2 = { 'B',NULL,NULL };
TreeNode n3 = { '*',&n1,&n2 };
TreeNode n4 = { 'C',NULL,NULL };
TreeNode n5 = { 'D',NULL,NULL };
TreeNode n6 = { '/',&n4,&n5 };
TreeNode n7 = { '+',&n3,&n6 };
element exp_ = &n7;

struct QueueNode {	// queue�� ���
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
		q->front = q->rear = temp;
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

void level_order(TreeNode *ptr) {
	QueueType q;
	init(&q);
	if (!ptr) return;
	enqueue(&q, ptr);	//������ ���� �ϳ� ����
	while (!is_empty(&q)) {
		ptr = dequeue(&q);			//�Ѱ��� ����
		std::cout << ptr->data << " ";
		if (ptr->left) enqueue(&q, ptr->left);	// ���� �ڽ��� �ֱ�
		if (ptr->right) enqueue(&q, ptr->right);	// ������ �ڽ��� �ֱ�
	}
}

int main()
{
	level_order(exp_);
	return 0;
}