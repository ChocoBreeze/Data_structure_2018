//topological sort 위상 정렬

#include<iostream>
const int MAX_SIZE = 100;
const int MAX_VERTICES = 50;
struct GraphNode {
	int vertex;
	GraphNode *link;
};
struct GraphType {
	int n; // 정점 개수
	GraphNode *adj_list[MAX_VERTICES]; // 헤드 포인터 배열
};

typedef int element;
const int MAX_STACK_SIZE = 100;
struct StackType {
	element stack[MAX_STACK_SIZE];
	int top;
};

void init(StackType *s) { // 초기화
	s->top = -1;
}

int is_empty(StackType *s) { // 비어있다면 1을 반환
	return (s->top == -1);
}

int is_full(StackType *s) {	// MAX_STACK_SIZE개수가 있다면 1을 반환
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item) { // 맨 위에 넣기
	if (is_full(s)) {
		std::cout << "overflow\n";
		return;
	}
	else s->stack[++(s->top)] = item;
}

element pop(StackType *s) {	// 맨 위에 있던 값 빼기 + 삭제
	if (is_empty(s)) {
		std::cout << "underflow\n";
		exit(1);
	}
	else return s->stack[(s->top)--];
}

void graph_init(GraphType *g) { // 초기화
	g->n = 0;
	for (int v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}
void topo_sort(GraphType *g) {
	StackType s;
	GraphNode *node;
	int* in_degree = new int[g->n];
	//모든 정점의 진입 차수 계산
	for (int i = 0; i < g->n; i++) in_degree[i] = 0; // 초기화
	for (int i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i];// 정점 i에서 나오는 간선들
		while (node != NULL) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}
	//진입 차수가 0인 정점을 스택에 삽입
	init(&s);
	for (int i = 0; i < g->n; i++) {
		if (in_degree[i] == 0) push(&s, i);
	}
	//위상 순서를 생성
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