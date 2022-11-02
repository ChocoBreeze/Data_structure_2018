#include<iostream>
#include<climits>
const int ARRAYSIZE = 7;	// 정점 수
const int INF = 1000;		// 무한대 - 연결 x
int weight[ARRAYSIZE][ARRAYSIZE] = { // 네트워크 인접 행렬
	{ 0,7,INF,INF,3,10,INF },
	{ 7,0,4,10,2,6,INF },
	{ INF,4,0,2,INF,INF,INF },
	{ INF,10,2,0,11,9,4 },
	{ 3,2,INF,11,0,INF,5 },
	{ 10,6,INF,9,INF,0,INF } ,
	{ INF,INF,INF,4,5,INF,0 } };
	
void floyd() {
	int weight_temp[ARRAYSIZE][ARRAYSIZE];
	for (int i = 0; i < ARRAYSIZE; i++) {
		for (int j = 0; j < ARRAYSIZE; j++) {
			weight_temp[i][j] = weight[i][j];
		}
	}
	for (int i = 0; i < ARRAYSIZE; i++) {
		for (int j = 0; j < ARRAYSIZE; j++) {
			for (int k = 0; k < ARRAYSIZE; k++) {
				if (weight_temp[j][i] + weight_temp[i][k] < weight_temp[j][k])
					weight_temp[j][k] = weight_temp[j][i] + weight_temp[i][k];
			}
		}
	}
	std::cout << "-Floyd- :\n";
	for (int j = 0; j < ARRAYSIZE; j++) {
		for (int i = 0; i < ARRAYSIZE; i++) {
			std::cout << j << " -> " << i << " : " << weight_temp[j][i] << std::endl;
		}
	}
}
int main()
{
	floyd();
	return 0;
}