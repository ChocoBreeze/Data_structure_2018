#include<iostream>
const int MAX_VERTICES = 7;
const int INF = 1000;
int weight[MAX_VERTICES][MAX_VERTICES] = {
	{0,29,INF,INF,INF,10,INF},
	{29,0,16,INF,INF,INF,15},
	{INF,16,0,12,INF,INF,INF},
	{INF,INF,12,0,22,INF,18},
	{INF,INF,INF,22,0,27,25},
	{10,INF,INF,INF,27,0,INF},
	{INF,15,INF,18,25,INF,0}
};
int selected[MAX_VERTICES];
int dist[MAX_VERTICES];

int get_min_vertex(int n) {	// 최소 dist[v] 값을 갖는 정점 반환
	int v, i;
	for (i = 0; i < n; i++) {
		if (!selected[i]) {
			v = i;
			break;
		}
	}
	for (i = 0; i < n; i++) {
		if (!selected[i] && (dist[i] < dist[v])) v = i;
	}
	return v;
}

void prim(int s, int n) {
	int u;
	for (u = 0; u < n; u++) {
		dist[u] = INF;
		selected[u] = 0;
	}
	dist[s] = 0;
	for (int i = 0; i < n; i++) {
		u = get_min_vertex(n);
		selected[u] = 1;
		if (dist[u] == INF) return;
		std::cout << u <<" ";
		for (int v = 0; v < n; v++) {
			if (weight[u][v] != INF)
				if (!selected[v] && weight[u][v] < dist[v])
					dist[v] = weight[u][v];
		}
	}
}

void main()
{
	prim(0, MAX_VERTICES);
}