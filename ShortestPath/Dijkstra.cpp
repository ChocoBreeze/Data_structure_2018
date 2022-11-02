#include<iostream>
#include<climits>
const int ARRAYSIZE = 7;	// 정점 수
const int INF = 1000;		// 무한대 - 연결 x
int weight[ARRAYSIZE][ARRAYSIZE] = { // 네트워크 인접 행렬
	{0,7,INF,INF,3,10,INF},
	{7,0,4,10,2,6,INF},
	{INF,4,0,2,INF,INF,INF},
	{INF,10,2,0,11,9,4},
	{3,2,INF,11,0,INF,5},
	{10,6,INF,9,INF,0,INF} ,
	{INF,INF,INF,4,5,INF,0} };
void dijkstra(int start) {
	int distance[ARRAYSIZE], s[ARRAYSIZE] = { 0, };
	int min, index = 0, min_pos;
	char goal;
	printf("-Dijkstra-\nInput : ");
	std::cin >> goal;	// A~G만을 입력받는다고 가정
	int goal_int = goal - 'A' + 1;
	for (int i = 0; i < ARRAYSIZE; i++) {
		distance[i] = weight[start][i];
	}
	s[start] = 1; // 방문 체크
	for (int i = 0; i<ARRAYSIZE - 1; i++) {
		min = INT_MAX; min_pos = -1;
		for (int j = 0; j < ARRAYSIZE; j++) {
			if (s[j] == 0 && distance[j] < min) { min = distance[j]; min_pos = j; }
		}
		s[min_pos] = 1;
		for (int j = 0; j < ARRAYSIZE; j++) {
			if (s[j] == 0) {
				if (distance[min_pos] + weight[min_pos][j] < distance[j])
					distance[j] = distance[min_pos] + weight[min_pos][j];
			}
		}
		if (min_pos == goal_int) { std::cout << "Shortest path : " << distance[goal_int] << std::endl; return; }
	}
}
int main()
{
	dijkstra(0);
	return 0;
}