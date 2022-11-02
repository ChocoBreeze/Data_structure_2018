#include <iostream>
const int MAX_SIZE = 100;
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

// 2022�� �߰�
auto swap_lambda = [](int& x, int& y, int& t) {
	t = x;
	x = y;
	y = t;
};

void inline swap_inline(int& x, int& y, int& t) {
	t = x; x = y; y = t;
}

/*
// �� �� �ɱ�?
template <typename T>
auto Swap_t = [](T& x, T& y, T& t) {
	t = x;
	x = y;
	y = t;
};
*/

//��� �������� ����

void selection_sort(int list[], int n) {
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) {
			if (list[j] < list[least]) least = j;
		}
		if (i != least) {
			// SWAP(list[i], list[least], temp);
			// swap_lambda(list[i], list[least], temp);
			swap_inline(list[i], list[least], temp);
		}
	}
}

void insertion_sort(int list[], int n) {
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--) {
			list[j + 1] = list[j];
		}
		list[j + 1] = key;	// ������ ��ġ�� ����.
	}
}

void bubble_sort(int list[], int n) {
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {	// ��, �� ���ڵ� �� --> ��ü
			if (list[j] > list[j + 1]) SWAP(list[j], list[j + 1], temp);
		}
	}
}

//shell sort -- ���� ���� ����(insertion sort)
void inc_insertion_sort(int list[], int first, int last, int gap) {
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap) {
			list[j + gap] = list[j];
		}
		list[j + gap] = key;
	}
}
void shell_sort(int list[], int n) {
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if (gap % 2 == 0) gap++;
		for (i = 0; i < gap; i++) {
			inc_insertion_sort(list, i, n - 1, gap);
		}
	}
}

//merge sort �պ� ���� -- �߰� ������� �ʿ�
int sorted[MAX_SIZE];
void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	while (i <= mid && j <= right) { // ��,�쿡 �ִ� ���� sorted�� �ֱ�
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}
	// �����ִ� �迭 ó��
	if (i > mid) for (l = j; l <= right; l++) sorted[k++] = list[l];
	else for (l = i; l <= mid; l++) sorted[k++] = list[l];
	// �迭 sorted�� ���� �迭�� ����
	for (l = left; l <= right; l++) list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right) { // �ڸ��� �͸�
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid); //����
		merge_sort(list, mid + 1, right); // ������
		merge(list, left, mid, right); // �ٽ� ��ġ��
	}
}

// quick sort
int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left]; // pivot�� ���� ���� ���ڶ�� ����
	do {
		do {
			low++;
		} while (low <= right && list[low] < pivot);
		do {
			high--;
		} while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);
	SWAP(list[left], list[high], temp);
	return high;
}

void quick_sort(int list[], int left, int right) {
	if (left < right) { // ������ 1�� �̻�
		int q = partition(list, left, right); // pivot�� �������� 2���� ���� ���� ���
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}