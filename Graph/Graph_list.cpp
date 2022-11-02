// �׷��� ����, �ʱ�ȭ, ���� ����,����, ���� ����,����, ����������� Ȯ��, ��������ã��, �׷�������
// ��������Ʈ
// ��ұ׷����� ����
#include<iostream>
const int MAX_VERTICES = 50;
struct GraphNode {
	int vertex;
	GraphNode *link;
};

struct GraphType {
	int n; // ���� ����
	GraphNode *adj_list[MAX_VERTICES]; // ��� ������ �迭
};

void graph_init(GraphType *g) { // �ʱ�ȭ
	g->n = 0;
	for (int v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}

void insert_vertex(GraphType *g,int v) { //���� ����
	if ((g->n) + 1 > MAX_VERTICES) {
		std::cout << "���� �ִ� ���� �ʰ�";
		return;
	}
	g->adj_list[v] = new GraphNode;
	g->n++;
}

void delete_vertex(GraphType *g, int v) { // ���� ����
	if (g->n == 0) return;
	GraphNode* node = g->adj_list[v];
	while (1) {
		if (node->link == NULL) break;
		GraphNode* temp = node;
		node = node->link;
		delete temp;
	}
	delete node;
}

void insert_edge(GraphType *g, int u, int v) { //���� ����(v->u)
	if (u >= g->n || v >= g->n) {
		std::cout << "�߸��� ���� ��ȣ";
		return;
	}
	GraphNode* node = new GraphNode;
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void delete_edge(GraphType *g, int u, int v) { // ���� ����(v->u)
	if (u >= g->n || v >= g->n) {
		std::cout << "�߸��� ���� ��ȣ";
		return;
	}
	GraphNode* node = g->adj_list[v];
	while (1)
	{
		if (node== NULL) break;
		if (node->link->vertex = v) {
			GraphNode* temp = node->link;
			node->link = temp->link;
			delete temp;
			break;
		}
	}
}

int visited[MAX_VERTICES];
void dfs(GraphType *g, int v) { // �迭
	GraphNode *w;
	visited[v] = 1;								// �湮 ǥ��
	std::cout << v;								// �湮 ���� ���
	for (w = g->adj_list[v]; w; w = w->link) {	// ���� ���� Ž��
		if (!visited[w->vertex]) dfs(g, w->vertex);
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
	GraphNode* w;
	QueueType q;
	init(&q);				
	visited[v] = 1;									//���� v �湮
	std::cout << v;								
	enqueue(&q, v);									//���� ���� q�� ����
	while (!is_empty(&q)) {
		v = dequeue(&q);							//q���� ���� ����
		for (w = g->adj_list[v]; w; w = w->link) {	//���� ���� Ž��
			if (!visited[w->vertex]) {				//�̹湮 ���� Ž��
				visited[w->vertex] = 1;				
				std::cout << w->vertex;				//�������
				enqueue(&q, w->vertex);				//�湮�� ������ ť�� ����
			}
		}
	}
}

//���� ����
int count = 0;
void find_connected_component(GraphType *g,int v) {
	int i;
	count = 0;
	for (GraphNode* w = g->adj_list[v]; w; w = w->link) {
		if (!visited[w->vertex]) {	//�湮 x�� ��쿡
			count++;
			dfs(g, w->vertex); // dfs or bfs �̿�.. --> visited[i]=count�� ����
		}
	}
}