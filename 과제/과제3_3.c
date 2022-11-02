#include<stdio.h>
#include<limits.h>
#define ARRAYSIZE 9					// 배열 크기
#define infinity 10000				// 무한대를 표시
int weight[9][9] = {
	{0, 7, infinity, infinity, infinity, infinity, 4, infinity, infinity},		//S
	{7, 0, 5, infinity, infinity, 2, infinity, infinity, infinity},				//A
	{infinity, 5, 0, 4, infinity, infinity, infinity, infinity, infinity},		//B
	{infinity, infinity, 4, 0, 2, infinity, infinity, infinity, 6},				//C
	{infinity,infinity, infinity, 2, 0, 3, infinity, 8, infinity},				//D
	{infinity, 2, infinity, infinity, 3, 0, 11, infinity, infinity },			//E
	{4, infinity, infinity, infinity, infinity, 11, 0, 9, infinity },			//F
	{infinity,infinity, infinity, infinity, 8, infinity, 9, 0, 1},				//G
	{infinity,infinity, infinity, 6, infinity, infinity, infinity, 1, 0}		//H
};
void dijkstra(int start) {				// 다익스트라 구현
	int distance[ARRAYSIZE], s[ARRAYSIZE] = { 0, };
	int min,index=0,min_pos;
	char goal;
	printf("-Dijkstra-\nInput : ");
	scanf("%c",&goal);	// A~H만을 도착점으로 입력받는다고 가정
	int goal_int = goal - 'A' + 1;
	for (int i = 0; i < ARRAYSIZE; i++) {
		distance[i] = weight[start][i];
	}
	s[start] = 1; // 방문 체크
	for(int i=0;i<ARRAYSIZE-1;i++) {
		min = INT_MAX; min_pos = -1;
		for (int j = 0; j < ARRAYSIZE; j++) {
			if (s[j] == 0 && distance[j] < min) { min = distance[j]; min_pos = j; }	// min_pos를 선택
		}
		s[min_pos] = 1;
		for (int j = 0; j < ARRAYSIZE; j++) {
			if (s[j] == 0) {
				if (distance[min_pos] + weight[min_pos][j] < distance[j])	// min_pos를 거치고 가는 경로와 바로 가는 경로 중 weight값이 작은 것을 선택
					distance[j] = distance[min_pos] + weight[min_pos][j];
			}
		}
		if (min_pos == goal_int) { printf("Shortest path : %d\n", distance[goal_int]); return; } // min_pos의 위치가 원하는 위치일 경우에 종료
	}
}
void floyd() {
	int weight_temp[ARRAYSIZE][ARRAYSIZE];
	for (int i = 0; i < ARRAYSIZE; i++) {
		for (int j = 0; j < ARRAYSIZE; j++) {
			weight_temp[i][j] = weight[i][j];		// 임시 배열에 값을 저장
		}
	}
	for (int k = 0; k<ARRAYSIZE; k++) {
		for (int i = 0; i < ARRAYSIZE; i++) {
			for (int j = 0; j < ARRAYSIZE; j++) {	// 정점 k를 지나는 경우와 바로 가는 경우를 비교해서 weight 값이 작은 것을 선택
				if (weight_temp[i][k] + weight_temp[k][j] < weight_temp[i][j]) weight_temp[i][j] = weight_temp[i][k] + weight_temp[k][j];
			}
		}
	}
	printf("-Floyd- :\n");
	for (int j = 0; j < ARRAYSIZE; j++) {
		for (int i = 0; i < ARRAYSIZE; i++) {	// 경우에 따른 출력
			if(j==0 && i==0) printf("S -> S : %d\t", weight_temp[j][i]);
			else if (j == 0) printf("S -> %c : %d\t", i + 'A' - 1, weight_temp[j][i]);
			else if (i == 0) printf("%c -> S : %d\t", j + 'A' - 1, weight_temp[j][i]);
			else printf("%c -> %c : %d\t", j + 'A' - 1, i + 'A' - 1, weight_temp[j][i]);
		}
		printf("\n");
	}
}
int main()
{
	dijkstra(0);	// 다익스트라를 시작정점과 함께 호출
	floyd();		// 플로이드 호출
	return 0;
}