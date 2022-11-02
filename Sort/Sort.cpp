#include <iostream>
const int MAX_SIZE = 100;
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

// 2022년 추가
auto swap_lambda = [](int& x, int& y, int& t) {
	t = x;
	x = y;
	y = t;
};

void inline swap_inline(int& x, int& y, int& t) {
	t = x; x = y; y = t;
}

/*
// 왜 안 될까?
template <typename T>
auto Swap_t = [](T& x, T& y, T& t) {
	t = x;
	x = y;
	y = t;
};
*/

//모두 오름차순 정렬

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
		list[j + 1] = key;	// 적절한 위치에 삽입.
	}
}

void bubble_sort(int list[], int n) {
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {	// 앞, 뒤 레코드 비교 --> 교체
			if (list[j] > list[j + 1]) SWAP(list[j], list[j + 1], temp);
		}
	}
}

//shell sort -- 삽입 정렬 개선(insertion sort)
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

//merge sort 합병 정렬 -- 추가 저장공간 필요
int sorted[MAX_SIZE];
void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	while (i <= mid && j <= right) { // 좌,우에 있는 값을 sorted에 넣기
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}
	// 남아있는 배열 처리
	if (i > mid) for (l = j; l <= right; l++) sorted[k++] = list[l];
	else for (l = i; l <= mid; l++) sorted[k++] = list[l];
	// 배열 sorted를 원래 배열에 복사
	for (l = left; l <= right; l++) list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right) { // 자르는 것만
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid); //왼쪽
		merge_sort(list, mid + 1, right); // 오른쪽
		merge(list, left, mid, right); // 다시 합치기
	}
}

// quick sort
int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left]; // pivot은 가장 왼쪽 숫자라고 가정
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
	if (left < right) { // 개수가 1개 이상
		int q = partition(list, left, right); // pivot을 기준으로 2개로 분할 한후 재귀
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}