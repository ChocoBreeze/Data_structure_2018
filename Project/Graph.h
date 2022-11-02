#pragma once
#include<string>
#include<utility>

using std::pair;
using std::wstring;

const int MAX_SIZE = 249;
const int MAX_ELEMENT = 250;
const int CAFE_NUMBER = 50;
const int RES_NUMBER = 248;
const int BAR_NUMBER = 22;

struct store_info {
	wstring name;
	wstring place;
	wstring range[2];
	int expected_cost;
	wstring time;
	wstring menu[3];
	wstring menu_price[3];
	wstring day_off;
};

class Graph {
private:
	int n;
	double **adj_mat;
public:
	Graph(int size);
	~Graph();
	void cal_similarity(store_info *s);			// jaccard_similarity - 지역, 큰 분류, 작은 분류, 예상 소모 비용
	void print_similarity();
	void print_3_stores(int choice, store_info *s);
};

Graph::Graph(int size) {
	n = size;
	adj_mat = new double*[n];
	for (int j = 0; j < n; j++) {
		adj_mat[j] = new double[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			adj_mat[i][j] = 0;
		}
	}
}

Graph::~Graph() {
}

void Graph::cal_similarity(store_info *s) {
	int cnt;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cnt = 0;
			if (i == j) continue;
			if (s[i].place.compare(s[j].place) == 0) cnt++;
			if (s[i].range[0].compare(s[j].range[0]) == 0) cnt++;
			if (s[i].range[1].compare(s[j].range[1]) == 0) cnt++;
			if ((double)s[i].expected_cost*0.9 <= s[j].expected_cost && s[j].expected_cost<= (double)s[i].expected_cost*1.1) cnt++;
			adj_mat[i][j] = (double)cnt / 4;
		}
	}
}

void Graph::print_similarity() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << this->adj_mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Graph::print_3_stores(int choice, store_info *s) {
	double *temp_mat = new double[n];
	int *index = new int[n];
	for (int i = 0; i < n; i++) {
		temp_mat[i] = adj_mat[choice][i];
		index[i] = i;
	}
	// bubble sort 내림차순
	double temp;
	int temp_index;
	for (int i = n-1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (temp_mat[j] < temp_mat[j + 1]) {
				temp = temp_mat[j]; temp_mat[j] = temp_mat[j + 1]; temp_mat[j + 1] = temp;
				temp_index = index[j]; index[j] = index[j + 1]; index[j + 1] = temp_index;
			}
		}
	}
	std::wcout.imbue(std::locale("kor"));	// 출력
	std::wcout << L"추천가게 목록 : \n";
	for (int i = 0; i < 3; i++) {
		std::wcout << s[index[i]].name << " ";
	}
	std::cout << std::endl;
	delete[] temp_mat;
	delete[] index;
}

class graph_human {
private:
	pair<double, double>*p;				// 각각 코사인 유사도, pcc 유사도
	int num_of_people;
	int n;
public:
	graph_human(int *array_[10], int num_people, int size, int* user);
	~graph_human();
	double cal_cosine_similarity(int *array_[10], int i, int* user);		// 0(같음) ~ 2(정반대)
	double cal_PCC_similarity(int *array_[10], int i, int* user);			//(음의 상관관계)-1 ~ 1(양의 상관관계)
	void print_3_stores_cosine(store_info* s);
	void print_3_stores_PCC(store_info* s);
};

graph_human::graph_human(int *array_[10], int num_people, int size, int* user) {
	n = size;
	num_of_people = num_people;
	p = new pair<double, double>[num_of_people];
	for (int i = 0; i < num_of_people; i++) {
		p[i].first = cal_cosine_similarity(array_, i, user);
		p[i].second = cal_PCC_similarity(array_, i, user);
	}
}

graph_human::~graph_human() {
	return;
}


double graph_human::cal_cosine_similarity(int *array_[10], int i, int* user) {
	double s1 = 0, s2 = 0, s3 = 0;
	for (int k = 0; k < n; k++) {
		s1 += (double)array_[i][k] * user[k];
		s2 += (double)array_[i][k] * array_[i][k];
		s2 += (double)user[k] * user[k];
	}
	return s1 / (sqrt(s2)*sqrt(s3));
}

double graph_human::cal_PCC_similarity(int *array_[10], int i, int* user) {
	double s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0;
	for (int k = 0; k < n; k++) {
		s1 += (double)array_[i][k] * user[k];
		s2 += (double)array_[i][k];
		s3 += (double)user[k];
		s4 += (double)array_[i][k] * array_[i][k];
		s5 += (double)user[k] * user[k];
	}
	return (s1 - (s2*s3 / n)) / ((s4 - (s2*s2 / n))*(s5 - (s3*s3 / n)));
}

void graph_human::print_3_stores_cosine(store_info* s) {	// 0~2
	double *temp_mat = new double[n];
	int *index = new int[n];
	for (int i = 0; i < n; i++) {
		temp_mat[i] = p[i].first;
		index[i] = i;
	}
	// bubble sort 오름차순
	double temp;
	int temp_index;
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (temp_mat[j] > temp_mat[j + 1]) {
				temp = temp_mat[j]; temp_mat[j] = temp_mat[j + 1]; temp_mat[j + 1] = temp;
				temp_index = index[j]; index[j] = index[j + 1]; index[j + 1] = temp_index;
			}
		}
	}
	std::wcout.imbue(std::locale("kor"));	// 출력
	std::wcout << L"1번 추천 : \n";
	for (int i = 0; i < 3; i++) {
		std::wcout << s[index[i]].name << " ";
	}
	std::cout << std::endl;
	delete[] temp_mat;
	delete[] index;
}

void graph_human::print_3_stores_PCC(store_info* s) {	// -1~1
	double *temp_mat = new double[n];
	int *index = new int[n];
	for (int i = 0; i < n; i++) {
		temp_mat[i] = p[i].second;
		index[i] = i;
	}
	// bubble sort 내림차순
	double temp;
	int temp_index;
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (temp_mat[j] < temp_mat[j + 1]) {
				temp = temp_mat[j]; temp_mat[j] = temp_mat[j + 1]; temp_mat[j + 1] = temp;
				temp_index = index[j]; index[j] = index[j + 1]; index[j + 1] = temp_index;
			}
		}
	}
	std::wcout.imbue(std::locale("kor"));	// 출력
	std::wcout << L"2번 추천 : \n";
	for (int i = 0; i < 3; i++) {
		std::wcout << s[index[i]].name << " ";
	}
	std::cout << std::endl;
	delete[] temp_mat;
	delete[] index;
}