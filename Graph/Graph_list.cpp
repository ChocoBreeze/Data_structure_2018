// 그래프 생성, 초기화, 정점 삽입,삭제, 간선 삽입,삭제, 공백상태인지 확인, 인접정점찾기, 그래프제거
// 인접리스트
// 희소그래프에 적합
#include<iostream>
const int MAX_VERTICES = 50;
struct GraphNode {
	int vertex;
	GraphNode *link;
};

struct GraphType {
	int n; // 정점 개수
	GraphNode *adj_list[MAX_VERTICES]; // 헤드 포인터 배열
};

void graph_init(GraphType *g) { // 초기화
	g->n = 0;
	for (int v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}

void insert_vertex(GraphType *g,int v) { //정점 삽입
	if ((g->n) + 1 > MAX_VERTICES) {
		std::cout << "정점 최대 개수 초과";
		return;
	}
	g->adj_list[v] = new GraphNode;
	g->n++;
}

void delete_vertex(GraphType *g, int v) { // 정점 삭제
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

void insert_edge(GraphType *g, int u, int v) { //간선 삽입(v->u)
	if (u >= g->n || v >= g->n) {
		std::cout << "잘못된 정점 번호";
		return;
	}
	GraphNode* node = new GraphNode;
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void delete_edge(GraphType *g, int u, int v) { // 간선 삭제(v->u)
	if (u >= g->n || v >= g->n) {
		std::cout << "잘못된 정점 번호";
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
void dfs(GraphType *g, int v) { // 배열
	GraphNode *w;
	visited[v] = 1;								// 방문 표시
	std::cout << v;								// 방문 정점 출력
	for (w = g->adj_list[v]; w; w = w->link) {	// 인접 정점 탐색
		if (!visited[w->vertex]) dfs(g, w->vertex);
	}
}

typedef int element;
struct QueueNode {	// queue의 노드
	element item;
	QueueNode* link;
};

struct QueueType {	//queue를 위한 구조체
	QueueNode *front, *rear;
};

void init(QueueType *q) { // 초기화
	q->front = q->rear = NULL;
}

void enqueue(QueueType *q, element item) { // 삽입
	QueueNode* temp = new QueueNode;
	temp->item = item;
	temp->link = NULL;
	if (is_empty(q)) { // queue가 공백 상태 --> front와 rear가 새로운 노드를 가리키게 함
		q->front = q->rear = temp;
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

int is_empty(QueueType *q) {
	return(q->front == NULL);
}

void bfs(GraphType *g, int v) { // 큐 + 배열
	GraphNode* w;
	QueueType q;
	init(&q);				
	visited[v] = 1;									//정점 v 방문
	std::cout << v;								
	enqueue(&q, v);									//시작 정점 q에 저장
	while (!is_empty(&q)) {
		v = dequeue(&q);							//q에서 정점 추출
		for (w = g->adj_list[v]; w; w = w->link) {	//인접 정점 탐색
			if (!visited[w->vertex]) {				//미방문 정점 탐색
				visited[w->vertex] = 1;				
				std::cout << w->vertex;				//정점출력
				enqueue(&q, w->vertex);				//방문할 정점을 큐에 삽입
			}
		}
	}
}

//연결 성분
int count = 0;
void find_connected_component(GraphType *g,int v) {
	int i;
	count = 0;
	for (GraphNode* w = g->adj_list[v]; w; w = w->link) {
		if (!visited[w->vertex]) {	//방문 x일 경우에
			count++;
			dfs(g, w->vertex); // dfs or bfs 이용.. --> visited[i]=count로 수정
		}
	}
}