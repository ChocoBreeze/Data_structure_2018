//topological sort ���� ����

#include<iostream>
const int MAX_SIZE = 100;
const int MAX_VERTICES = 50;
struct GraphNode {
	int vertex;
	GraphNode *link;
};
struct GraphType {
	int n; // ���� ����
	GraphNode *adj_list[MAX_VERTICES]; // ��� ������ �迭
};

typedef int element;
const int MAX_STACK_SIZE = 100;
struct StackType {
	element stack[MAX_STACK_SIZE];
	int top;
};

void init(StackType *s) { // �ʱ�ȭ
	s->top = -1;
}

int is_empty(StackType *s) { // ����ִٸ� 1�� ��ȯ
	return (s->top == -1);
}

int is_full(StackType *s) {	// MAX_STACK_SIZE������ �ִٸ� 1�� ��ȯ
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item) { // �� ���� �ֱ�
	if (is_full(s)) {
		std::cout << "overflow\n";
		return;
	}
	else s->stack[++(s->top)] = item;
}

element pop(StackType *s) {	// �� ���� �ִ� �� ���� + ����
	if (is_empty(s)) {
		std::cout << "underflow\n";
		exit(1);
	}
	else return s->stack[(s->top)--];
}

void graph_init(GraphType *g) { // �ʱ�ȭ
	g->n = 0;
	for (int v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}
void topo_sort(GraphType *g) {
	StackType s;
	GraphNode *node;
	int* in_degree = new int[g->n];
	//��� ������ ���� ���� ���
	for (int i = 0; i < g->n; i++) in_degree[i] = 0; // �ʱ�ȭ
	for (int i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i];// ���� i���� ������ ������
		while (node != NULL) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}
	//���� ������ 0�� ������ ���ÿ� ����
	init(&s);
	for (int i = 0; i < g->n; i++) {
		if (in_degree[i] == 0) push(&s, i);
	}
	//���� ������ ����
	while (!is_empty(&s)) {
		int w;
		w = pop(&s);
		std::cout << w;
		node = g->adj_list[w];
		while (node != NULL) {
			int u = node->vertex;
			in_degree[u]--;
			if (in_degree[u] == 0) push(&s, u);
			node = node->link;
		}
	}
	delete in_degree;
	return;
}