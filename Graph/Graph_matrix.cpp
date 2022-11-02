// �׷��� ����, �ʱ�ȭ, ���� ����,����, ���� ����,����, ����������� Ȯ��, ��������ã��, �׷�������
// �������
#include<iostream>
const int MAX_VERTICES = 50;
struct GraphType {
	int n; // ���� ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
};

void graph_init(GraphType *g) { // �ʱ�ȭ
	g->n = 0;
	for (int r = 0; r < MAX_VERTICES; r++) {
		for (int c = 0; c < MAX_VERTICES; c++) {
			g->adj_mat[r][c] = 0;
		}
	}
}

void insert_vertex(GraphType *g) { // ���� ����
	if ((g->n) + 1 > MAX_VERTICES) {
		std::cout << "���� �ִ� ���� �ʰ�";
		return;
	}
	g->n++;
}

void delete_vertex(GraphType *g,int v) { // ���� ����
	if (g->n == 0) return;
	else {
		for (int i = 0; i < g->n; i++) {
			g->adj_mat[i][v] = 0;
			g->adj_mat[v][i] = 0;
		}
	}
	g->n--;
}

void insert_vertex(GraphType *g,int u,int v) { //���� ����
	if (u >= g->n || v >= g->n) {
		std::cout << "�߸��� ���� ��ȣ";
		return;
	}
	g->adj_mat[u][v] = 1;
	g->adj_mat[v][u] = 1;
}

void delete_vertex(GraphType *g,int u,int v) {
	if (u >= g->n || v >= g->n) {
		std::cout << "�߸��� ���� ��ȣ";
		return;
	}
	g->adj_mat[u][v] = 0;
	g->adj_mat[v][u] = 0;
}

int visited[MAX_VERTICES];
void dfs(GraphType *g, int v) {	// �迭
	visited[v] = 1;
	std::cout << v;
	for (int w = 0; w<g->n; w++) {	// ���� ���� Ž��
		if (g->adj_mat[v][w] && !visited[w]) dfs(g, w);
	}
}

typedef int element;
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

int is_empty(QueueType *q) {
	return(q->front == NULL);
}

void bfs(GraphType *g, int v) { // ť + �迭
	int w;
	QueueType q;
	init(&q);
	visited[v] = 1;									//���� v �湮
	std::cout << v;
	enqueue(&q, v);									//���� ���� q�� ����
	while (!is_empty(&q)) {
		v = dequeue(&q);							//q���� ���� ����
		for (w = 0; w<g->n; w++) {					//���� ���� Ž��
			if (g->adj_mat[v][w] && !visited[w]) {	//�̹湮 ���� Ž��
				visited[w] = 1;
				std::cout << w;						//�������
				enqueue(&q, w);						//�湮�� ������ ť�� ����
			}
		}
	}
}

//���� ����
int count = 0;
void find_connected_component(GraphType *g) {
	int i;
	count = 0;
	for (i = 0; i < g->n; i++) {
		if (!visited[i]) {	//�湮 x�� ��쿡
			count++;
			dfs(g, i); // dfs or bfs �̿�.. --> visited[i]=count�� ����
		}
	}
}