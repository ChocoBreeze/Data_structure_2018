#include<iostream>
const int MAX_VERTICES = 100;
const int INF = 1000;
int parent[MAX_VERTICES];	// 부모 노드
int num[MAX_VERTICES];		// 각 집합의 크기
struct element {
	int key;		// 간선 가중치
	int u;			// 정점 1
	int v;			// 정점 2
};
const int MAX_ELEMENT = 200;
struct HeapType {
	element heap[MAX_ELEMENT];
	int heap_size;	// 총 노드의 수
};

void init(HeapType *h) {
	h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item) { //최대 히프
	int i = ++(h->heap_size);

	//트리를 거슬러 올라가 부모노드와 비교
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // 새 노드 삽입
}

element delete_min_heap(HeapType *h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 큰 자식노드를 활용
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key) child++;
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// 배열 인덱스를 포인터처럼 생각하여 구현
void set_init(int n) {		// 초기화
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
		num[i] = -1;
	}
}

int set_find(int vertex) { // vertex가 속하는 집합 반환
	int p, s, i = 1;
	for (i = vertex; (p = parent[i]) >= 0; i = p); // 루트노드까지 반복
	s = i; // 집합의 대표 원소
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s;	// 집합의 모든 원소들의 부모를 s로 설정
	return s;
}

void set_union(int s1, int s2) { //2원소가 속한 집합 합치기
	if (num[s1] < num[s2]) {
		parent[s1] = s2;
		num[s2] += num[s1];
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

void insert_heap_edge(HeapType *h, int u, int v, int weight) {	// 정점 u와 정점 v를 연결하는 가중치가 weight인 간선을 히프에 삽입
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_min_heap(h, e);
}

void insert_all_edges(HeapType *h) {	// 인접 행렬이나 인접 리스트에서 간선들을 읽어서 최소 히프에 삽입
	insert_heap_edge(h, 0, 1, 29);
	insert_heap_edge(h, 1, 2, 16);
	insert_heap_edge(h, 2, 3, 12);
	insert_heap_edge(h, 3, 4, 22);
	insert_heap_edge(h, 4, 5, 27);
	insert_heap_edge(h, 5, 0, 10);
	insert_heap_edge(h, 6, 1, 15);
	insert_heap_edge(h, 6, 3, 18);
	insert_heap_edge(h, 6, 4, 25);
}

void kruskal(int n) {
	int edge_accepted = 0;									// 현재까지 선택된 간선의 수
	HeapType h;												// 최소 히프	
	int uset, vset;											// 정점 u와 정점 v의 집합 번호
	element e;												// 히프 요소
	init(&h);												// 히프 초기화
	insert_all_edges(&h);									// 히프에 간선 삽입
	set_init(n);											// 집합 초기화
	while (edge_accepted < (n - 1)) {						// 간선수 < n-1
		e = delete_min_heap(&h);							// 최소 히프에서 삭제
		uset = set_find(e.u);								// 정점 u의 집합 번호
		vset = set_find(e.v);								// 정점 v의 집합 번호
		if (uset != vset) {									// 서로 속한 집합이 다르면
			std::cout << e.u  <<" "<< e.v << " " << e.key << std::endl;
			edge_accepted++;
			set_union(uset, vset);							// 두 집합 합치기
		}
	}
}

void main()
{
	kruskal(7);
}