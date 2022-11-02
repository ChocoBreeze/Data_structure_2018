#include<iostream>
const int MAX_VERTICES = 100;
const int INF = 1000;
int parent[MAX_VERTICES];	// �θ� ���
int num[MAX_VERTICES];		// �� ������ ũ��
struct element {
	int key;		// ���� ����ġ
	int u;			// ���� 1
	int v;			// ���� 2
};
const int MAX_ELEMENT = 200;
struct HeapType {
	element heap[MAX_ELEMENT];
	int heap_size;	// �� ����� ��
};

void init(HeapType *h) {
	h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item) { //�ִ� ����
	int i = ++(h->heap_size);

	//Ʈ���� �Ž��� �ö� �θ���� ��
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // �� ��� ����
}

element delete_min_heap(HeapType *h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ�� �� �� ū �ڽĳ�带 Ȱ��
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key) child++;
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// �迭 �ε����� ������ó�� �����Ͽ� ����
void set_init(int n) {		// �ʱ�ȭ
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
		num[i] = -1;
	}
}

int set_find(int vertex) { // vertex�� ���ϴ� ���� ��ȯ
	int p, s, i = 1;
	for (i = vertex; (p = parent[i]) >= 0; i = p); // ��Ʈ������ �ݺ�
	s = i; // ������ ��ǥ ����
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s;	// ������ ��� ���ҵ��� �θ� s�� ����
	return s;
}

void set_union(int s1, int s2) { //2���Ұ� ���� ���� ��ġ��
	if (num[s1] < num[s2]) {
		parent[s1] = s2;
		num[s2] += num[s1];
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

void insert_heap_edge(HeapType *h, int u, int v, int weight) {	// ���� u�� ���� v�� �����ϴ� ����ġ�� weight�� ������ ������ ����
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_min_heap(h, e);
}

void insert_all_edges(HeapType *h) {	// ���� ����̳� ���� ����Ʈ���� �������� �о �ּ� ������ ����
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
	int edge_accepted = 0;									// ������� ���õ� ������ ��
	HeapType h;												// �ּ� ����	
	int uset, vset;											// ���� u�� ���� v�� ���� ��ȣ
	element e;												// ���� ���
	init(&h);												// ���� �ʱ�ȭ
	insert_all_edges(&h);									// ������ ���� ����
	set_init(n);											// ���� �ʱ�ȭ
	while (edge_accepted < (n - 1)) {						// ������ < n-1
		e = delete_min_heap(&h);							// �ּ� �������� ����
		uset = set_find(e.u);								// ���� u�� ���� ��ȣ
		vset = set_find(e.v);								// ���� v�� ���� ��ȣ
		if (uset != vset) {									// ���� ���� ������ �ٸ���
			std::cout << e.u  <<" "<< e.v << " " << e.key << std::endl;
			edge_accepted++;
			set_union(uset, vset);							// �� ���� ��ġ��
		}
	}
}

void main()
{
	kruskal(7);
}