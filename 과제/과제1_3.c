#include<stdio.h>
void zero_to_one(int(*a)[10], int x, int y)
{
	a[x][y] = 1; // 0이였던 값을 1로 바꾼다.
	if (x>0 && a[x - 1][y] == 0) zero_to_one(a, x - 1, y); // 위쪽을 확인해 0이면 재귀호출
	if (x<10 && a[x + 1][y] == 0) zero_to_one(a, x + 1, y);	// 아래쪽을 확인해 0이면 재귀호출
	if (y>0 && a[x][y - 1] == 0) zero_to_one(a, x, y - 1);	// 왼쪽을 확인해 0이면 재귀호출
	if (y<10 && a[x][y + 1] == 0) zero_to_one(a, x, y + 1);	// 오른쪽을 확인해 0이면 재귀호출
}
int main()
{
	int i, j;
	int a[10][10] = { { 2,2,2,2,2,2,2,2,2,2 },{ 2,2,2,2,2,2,2,2,2,2 },{ 2,2,2,0,0,0,0,2,2,2 },{ 2,2,2,2,0,0,0,2,2,2 },{ 2,2,2,2,0,0,0,2,2,2 },{ 2,2,2,2,0,0,0,0,2,2 }
	,{ 2,2,2,2,0,2,2,2,2,2 },{ 2,2,2,2,0,2,2,2,2,2 },{ 2,2,2,2,0,2,2,2,2,2 } ,{ 2,2,2,2,2,2,2,2,2,2 } }; // 초기화
	printf("Before\n");
	for (i = 0; i < 10; i++) { // 0일 때의 상태를 출력한다.
		for (j = 0; j < 10; j++) {
			printf("%d", a[i][j]);
		}
		printf("\n");
	}
	zero_to_one(a, 5, 4); // 바꿀 배열의 주소와 처음 x좌표, y좌표를 매개변수로 대입한다
	printf("After\n");
	for (i = 0; i < 10; i++) { // 0이 1로 바뀌고 난 후의 상태를 보여준다.
		for (j = 0; j < 10; j++) {
			printf("%d", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}