// 그래프 생성, 초기화, 정점 삽입,삭제, 간선 삽입,삭제, 공백상태인지 확인, 인접정점찾기, 그래프제거
// 인접행렬
#include<iostream>
const int MAX_VERTICES = 50;
struct GraphType {
	int n; // 정점 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
};

void graph_init(GraphType *g) { // 초기화
	g->n = 0;
	for (int r = 0; r < MAX_VERTICES; r++) {
		for (int c = 0; c < MAX_VERTICES; c++) {
			g->adj_mat[r][c] = 0;
		}
	}
}

void insert_vertex(GraphType *g) { // 정점 삽입
	if ((g->n) + 1 > MAX_VERTICES) {
		std::cout << "정점 최대 개수 초과";
		return;
	}
	g->n++;
}

void delete_vertex(GraphType *g,int v) { // 정점 삭제
	if (g->n == 0) return;
	else {
		for (int i = 0; i < g->n; i++) {
			g->adj_mat[i][v] = 0;
			g->adj_mat[v][i] = 0;
		}
	}
	g->n--;
}

void insert_vertex(GraphType *g,int u,int v) { //간선 삽입
	if (u >= g->n || v >= g->n) {
		std::cout << "잘못된 정점 번호";
		return;
	}
	g->adj_mat[u][v] = 1;
	g->adj_mat[v][u] = 1;
}

void delete_vertex(GraphType *g,int u,int v) {
	if (u >= g->n || v >= g->n) {
		std::cout << "잘못된 정점 번호";
		return;
	}
	g->adj_mat[u][v] = 0;
	g->adj_mat[v][u] = 0;
}

int visited[MAX_VERTICES];
void dfs(GraphType *g, int v) {	// 배열
	visited[v] = 1;
	std::cout << v;
	for (int w = 0; w<g->n; w++) {	// 인접 정점 탐색
		if (g->adj_mat[v][w] && !visited[w]) dfs(g, w);
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
	int w;
	QueueType q;
	init(&q);
	visited[v] = 1;									//정점 v 방문
	std::cout << v;
	enqueue(&q, v);									//시작 정점 q에 저장
	while (!is_empty(&q)) {
		v = dequeue(&q);							//q에서 정점 추출
		for (w = 0; w<g->n; w++) {					//인접 정점 탐색
			if (g->adj_mat[v][w] && !visited[w]) {	//미방문 정점 탐색
				visited[w] = 1;
				std::cout << w;						//정점출력
				enqueue(&q, w);						//방문할 정점을 큐에 삽입
			}
		}
	}
}

//연결 성분
int count = 0;
void find_connected_component(GraphType *g) {
	int i;
	count = 0;
	for (i = 0; i < g->n; i++) {
		if (!visited[i]) {	//방문 x일 경우에
			count++;
			dfs(g, i); // dfs or bfs 이용.. --> visited[i]=count로 수정
		}
	}
}