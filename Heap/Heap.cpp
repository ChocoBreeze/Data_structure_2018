#include <iostream>
const int MAX_ELEMENT = 200;
struct element{
	int key;
};
struct HeapType {
	element heap[MAX_ELEMENT];
	int heap_size;	// 총 노드의 수
};

void init(HeapType *h) {
	h->heap_size = 0;
}

void insert_max_heap(HeapType *h, element item) { //최대 히프
	int i=++(h->heap_size);

	//트리를 거슬러 올라가 부모노드와 비교
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // 새 노드 삽입
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

element delete_max_heap(HeapType *h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 큰 자식노드를 활용
		if ((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key) child++;
		if (temp.key >= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

element delete_min_heap(HeapType *h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 작은 자식노드를 활용
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key) child++;
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void print_heap(HeapType *h) {
	for (int i = 1; i <= h->heap_size; i++)
		std::cout << h->heap[i].key << " ";
}

void main()
{
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };
	element e4, e5, e6;
	HeapType heap;	// 하프 생성
	init(&heap);	// 초기화
	// 삽입 
	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	insert_max_heap(&heap, e3);
	print_heap(&heap);
	// 삭제
	e4 = delete_max_heap(&heap);
	std::cout << e4.key << " ";
	e5 = delete_max_heap(&heap);
	std::cout << e5.key << " ";
	e6 = delete_max_heap(&heap);
	std::cout << e6.key << " ";
	std::cout << std::endl;
	// 삽입 
	insert_min_heap(&heap, e1);
	insert_min_heap(&heap, e2);
	insert_min_heap(&heap, e3);
	print_heap(&heap);
	// 삭제
	e4 = delete_min_heap(&heap);
	std::cout << e4.key << " ";
	e5 = delete_min_heap(&heap);
	std::cout << e5.key << " ";
	e6 = delete_min_heap(&heap);
	std::cout << e6.key << " ";
}