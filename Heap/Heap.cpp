#include <iostream>
const int MAX_ELEMENT = 200;
struct element{
	int key;
};
struct HeapType {
	element heap[MAX_ELEMENT];
	int heap_size;	// �� ����� ��
};

void init(HeapType *h) {
	h->heap_size = 0;
}

void insert_max_heap(HeapType *h, element item) { //�ִ� ����
	int i=++(h->heap_size);

	//Ʈ���� �Ž��� �ö� �θ���� ��
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // �� ��� ����
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

element delete_max_heap(HeapType *h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ�� �� �� ū �ڽĳ�带 Ȱ��
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
		// ���� ����� �ڽĳ�� �� �� ���� �ڽĳ�带 Ȱ��
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
	HeapType heap;	// ���� ����
	init(&heap);	// �ʱ�ȭ
	// ���� 
	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	insert_max_heap(&heap, e3);
	print_heap(&heap);
	// ����
	e4 = delete_max_heap(&heap);
	std::cout << e4.key << " ";
	e5 = delete_max_heap(&heap);
	std::cout << e5.key << " ";
	e6 = delete_max_heap(&heap);
	std::cout << e6.key << " ";
	std::cout << std::endl;
	// ���� 
	insert_min_heap(&heap, e1);
	insert_min_heap(&heap, e2);
	insert_min_heap(&heap, e3);
	print_heap(&heap);
	// ����
	e4 = delete_min_heap(&heap);
	std::cout << e4.key << " ";
	e5 = delete_min_heap(&heap);
	std::cout << e5.key << " ";
	e6 = delete_min_heap(&heap);
	std::cout << e6.key << " ";
}