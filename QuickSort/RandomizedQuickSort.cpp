#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int CountAll;
int Partition(int a[], int p, int r) {
	int x, i, temp, count = 0;
	x = a[r];
	i = p - 1;
	printf("Pivot : %d", x);
	for (int j = p; j <= r - 1; j++) {
		count++;
		if (a[j] <= x) {
			i = i + 1;
			{ temp = a[i]; a[i] = a[j]; a[j] = temp; }
		}
	}
	printf("\t반복횟수 : %d\n", count);
	CountAll += count;
	{ temp = a[i + 1]; a[i + 1] = a[r]; a[r] = temp; }
	return i + 1;

}

int Randomized_Partition(int a[], int p, int r) {
	int i, temp;
	i = (rand() % (r - p + 1)) + p;
	{temp = a[i]; a[i] = a[r]; a[r] = temp; }
	return Partition(a, p, r);
}

void Randomized_QuickSort(int a[], int p, int r) {
	int q;
	if (p < r) {
		q = Randomized_Partition(a, p, r);
		Randomized_QuickSort(a, p, q - 1);
		Randomized_QuickSort(a, q + 1, r);
	}
}

int main()
{
	srand(time(NULL));
	int a[5][20] = {
		{ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 }
		,{ 31, 71, 1, 37, 57, 79, 64, 5, 90, 41, 9, 2, 15, 86, 9, 12, 20, 38, 49, 12 }
		,{ 19, 44, 20, 77, 56, 99, 15, 56, 69, 64, 4, 65, 11, 80, 41, 47, 42, 4, 69, 12 }
		,{ 97, 90, 74, 67, 54, 53, 1, 66, 13, 11, 72, 87, 38, 65, 23, 85, 24, 80, 96, 98 }
		,{ 63, 92, 18, 40, 82, 58, 72, 37, 42, 82, 90, 11, 53, 97, 1, 56, 66, 67, 76, 37 }
	};
	int temp[20];
	for (int i = 0; i < 5; i++) {
		printf("%d번째 자료\n", i + 1);
		for (int j = 0; j < 20; j++) {
			temp[j] = a[i][j];
		}
		CountAll = 0;
		Randomized_QuickSort(temp, 0, 19);
		printf("총 반복횟수 : %d\n\n\n", CountAll);
	}
    return 0;
}

