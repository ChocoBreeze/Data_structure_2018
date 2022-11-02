// heap sort
#include<iostream>
const int MAX_ELEMENT = 200;
struct element {
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
	int i = ++(h->heap_size);

	//Ʈ���� �Ž��� �ö� �θ���� ��
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
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
		// ���� ����� �ڽĳ�� �� �� ���� �ڽĳ�带 Ȱ��
		if ((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key) child++;
		if (temp.key >= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void heap_sort(element a[], int n) {
	HeapType h;

	init(&h);
	for (int i = 0; i < n; i++) {
		insert_max_heap(&h, a[i]);
	}
	for (int i = (n - 1); i >= 0; i--) {
		a[i] = delete_max_heap(&h);
	}
}
