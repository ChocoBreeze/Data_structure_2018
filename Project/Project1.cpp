#include<cstdlib>
#include<iostream>
#include<fstream>
#include<locale>
#include"Graph.h"

store_info store[CAFE_NUMBER+RES_NUMBER+BAR_NUMBER];
store_info restaurant[RES_NUMBER];
store_info cafe_snack[CAFE_NUMBER];
store_info bar[BAR_NUMBER];
struct HeapType {
	store_info heap[MAX_ELEMENT];
	int heap_size;	// 총 노드의 수
};

// 힙 정렬을 위한 임시 배열
HeapType restaurant_temp;
HeapType c_s_temp;
HeapType bar_temp;

void init(HeapType *h) {
	h->heap_size = 0;
}

void insert_max_heap(HeapType *h, store_info item) { //최대 히프
	int i = ++(h->heap_size);
	//트리를 거슬러 올라가 부모노드와 비교
	while ((i != 1) && (item.expected_cost > h->heap[i / 2].expected_cost)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // 새 노드 삽입
}

store_info delete_max_heap(HeapType *h) {
	int parent, child;
	store_info item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 큰 자식노드를 활용
		if ((child < h->heap_size) && (h->heap[child].expected_cost) < h->heap[child + 1].expected_cost) child++;
		if (temp.expected_cost >= h->heap[child].expected_cost) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
using std::cin;
using std::cout;
using std::wcout;
using std::wcin;
using std::wifstream;
using std::ifstream;
using std::string;

//첫 번째 기능 = 가격순으로 보고 싶을 경우에 예상 지출 비용 순으로 가게 출력
void print_by_expected_cost() {
	int choice;
	cout << "첫 번째 기능(가격오름차순 출력) : 1~3까지 숫자 중 선택해주세요 (1: 식당 2: 술집 3: 카페 및 간식) \n입력 : ";
	cin >> choice;
	switch (choice) {
	case 1:		// 식당
		for (int i = 0; i < RES_NUMBER; i++) {
			wcout << i << "번째 가게이름 : " << restaurant[i].name << " 예상 지출 비용 : ";
			cout << restaurant[i].expected_cost << std::endl;
		}
		break;
	case 2:		// 술집
		for (int i = 0; i < BAR_NUMBER; i++) {
			wcout << i << ": " << bar[i].name << " 예상 지출 비용 : ";
			cout << bar[i].expected_cost << std::endl;
		}
		break;
	case 3:		// 카페 및 간식
		for (int i = 0; i < CAFE_NUMBER; i++) {
			wcout << i << ": " << cafe_snack[i].name << " ";
			cout << cafe_snack[i].expected_cost << std::endl;
		}
		break;
	}
}

//두 번째 기능 = 검색
void search() {	
	int choice, choice_deeper;
	wstring str;
	cout << "두 번째 기능(검색) : 1~3까지 숫자 중 선택해주세요 (1: 식당 2: 술집 3: 카페 및 간식) \n입력 : ";
	cin >> choice;
	cout << "세부 검색\n : 1~3까지 숫자 중 선택해주세요 (1: 위치 2: 큰 범주 3: 작은 범주) \n입력 : ";
	cin >> choice_deeper;
	switch (choice) {
	case 1:	// 식당
		switch (choice_deeper) {
		case 1:	// 위치
			cout << "검색 가능한 위치 : 동선동(성신여대), 용두동, 이캠, 전농동, 정문, 정후, 제기동, 종암동, 참살이, 청량리동\n";
			wcin >> str;
			for (int i = 0, j = 0; i < RES_NUMBER; i++)
				if (restaurant[i].place.compare(str) == 0) wcout << (++j) << "번째 가게이름 : " << restaurant[i].name << std::endl;
			break;
		case 2:	// 큰 범주
			cout << "검색 가능한 큰 범주 : 베트남, 분식, 뷔페, 양식, 인도, 일식, 중식, 한식\n";
			wcin >> str;
			for (int i = 0, j = 0; i < RES_NUMBER; i++)
				if (restaurant[i].range[0].compare(str) == 0) wcout << (++j) << "번째 가게이름 : " << restaurant[i].name << std::endl;
			break;
		case 3:	// 작은 범주
			cout << "검색 가능한 작은 범주 : 회, 햄버거, 해물,생선, 해장국, 해물, 핫도그, 함박스테이크, 한정식, 피자, 피자,치킨, 한식뷔페, 퓨전,튀김, 퓨전, 파스타, 탕류, 커리, 칼국수, 치킨, 초밥, 채식뷔페, 참치회, 찜닭, 찌개류, 찌개, 전골, 짬뽕, 짜장면, 중화요리, 죽, 족발, 제육볶음, 전, 이탈리안, 육류,고기, 우삼겹, 우동, 알밥, 쌀국수, 순두부, 순대, 소고기면, 소고기, 설렁탕, 샤브샤브, 생선회, 샐러드, 샌드위치, 삼계탕, 삼겹살, 사케동, 뼈해장국, 비빔밥, 분식, 부리또, 부대찌개, 부대볶음, 보쌈, 밥버거, 면, 만둣국, 라멘, 떡볶이, 두루치기, 돼지갈비, 돌솥밥, 돈부리, 돈까스,우동, 돈까스, 도시락, 덮밥, 냉면, 꿔바로우, 김치찌개, 김밥, 규카츠, 국수, 국밥, 교자, 곱창, 곰탕,만두, 고기, 갈비탕, 갈비찜, 갈매기살, 갈비\n";
			wcin >> str;
			for (int i = 0, j = 0; i < RES_NUMBER; i++)
				if (restaurant[i].range[1].compare(str) == 0) wcout << (++j) << "번째 가게이름 : " << restaurant[i].name << std::endl;
			break;
		}
		break;
	case 2:	// 술집
		switch (choice_deeper) {
		case 1:	// 위치
		case 2:
		case 3:
			cout << "술집은 큰 범주와 작은 범주가 모두 술집으로 동일하므로 위치로만 검색 가능합니다.\n";
			cout << "검색 가능한 위치 : 동선동(성신여대), 정후, 제기동, 참살이\n";
			wcin >> str;
			for (int i = 0, j = 0; i < BAR_NUMBER; i++)
				if (bar[i].place.compare(str) == 0) wcout << (++j) << "번째 가게이름 : " << bar[i].name << std::endl;
			break;
		}
		break;
	case 3:	 // 카페
		switch (choice_deeper) {
		case 1:	// 위치
			cout << "검색 가능한 위치 : 개운사길, 동선동(성신여대), 문과캠, 안암동, 이캠, 정후, 제기동, 참살이\n";
			wcin >> str;
			for (int i = 0, j = 0; i < CAFE_NUMBER; i++)
				if (cafe_snack[i].place.compare(str) == 0) wcout << (++j) << "번째 가게이름 : " << cafe_snack[i].name << std::endl;
			break;
		case 2:	// 큰 범주
			cout << "검색 가능한 큰 범주 : 간식, 카페\n";
			wcin >> str;
			for (int i = 0, j = 0; i < CAFE_NUMBER; i++)
				if (cafe_snack[i].range[0].compare(str) == 0) wcout << (++j) << "번째 가게이름 : " << cafe_snack[i].name << std::endl;
			break;
		case 3:	// 작은 범주
			cout << "검색 가능한 작은 범주 : 제과,베이커리, 샌드위치, 아이스크림, 카페, 커피전문점, 테마카페\n";
			wcin >> str;
			for (int i = 0, j = 0; i < CAFE_NUMBER; i++)
				if (cafe_snack[i].range[1].compare(str) == 0) wcout << (++j) << "번째 가게이름 : " << cafe_snack[i].name << std::endl;
			break;
		}
		break;
	}
}

//가게 간의 유사도 측정 - jaccard 유사도 
//세 번째 기능 = 1개의 가게 입력 시 그와 유사한 가게 추천
void recommend_3_stores() {
	int choice;
	Graph c_s = Graph(CAFE_NUMBER);
	c_s.cal_similarity(cafe_snack);
	Graph res = Graph(RES_NUMBER);
	res.cal_similarity(restaurant);
	Graph bar_ = Graph(BAR_NUMBER);
	bar_.cal_similarity(bar);
	cout << "세 번째 기능(하나의 가게 입력 시 유사한 가게 추천)\n : 1~3까지 숫자 중 선택해주세요 (1: 식당 2: 술집 3: 카페 및 간식) \n입력 : ";
	cin >> choice;
	switch (choice) {
	case 1:		// 식당
		for (int i = 0; i < RES_NUMBER; i++)
			wcout << i << ": " << restaurant[i].name << " ";
		cout << "\n방문했던 가게를 하나 골라 주세요(숫자)  \n";
		cin >> choice;
		res.print_3_stores(choice, restaurant);
		break;
	case 2:		// 술집
		for (int i = 0; i < BAR_NUMBER; i++)
			wcout << i << ": " << bar[i].name << " ";
		cout << "\n방문했던 가게를 하나 골라 주세요(숫자)  \n";
		cin >> choice;
		bar_.print_3_stores(choice, bar);
		break;
	case 3:		// 카페 및 간식
		for (int i = 0; i < CAFE_NUMBER; i++)
			wcout << i << ": " << cafe_snack[i].name << " ";
		cout << "\n방문했던 가게를 하나 골라 주세요(숫자)  \n";
		cin >> choice;
		c_s.print_3_stores(choice, cafe_snack);
		break;
	}
	c_s.~Graph();
	res.~Graph();
	bar_.~Graph();
}

// 카페에 한정한 예시
// 50개 평점 등록시 좋은 평점을 가질 가게 추천
void recommend_by_grade_cafe_version() {
	cout << "네 번째 기능(모든 카페들의 평점 입력 시 유사한 가게 추천)(0~5 사이의 숫자로 50개 입력해주세요)\n입력 : ";
	wcout.imbue(std::locale("kor"));	// 출력
	wcin.imbue(std::locale("kor"));		// 출력
	int i, j;
	ifstream fin;
	fin.open("cafe_simulation.txt");						// 기존 자료 - 평점
	if (!fin.is_open()) {
		cout << "파일을 열 수 없습니다. \n" << std::endl;
		exit(EXIT_FAILURE);
	}
	int* cafe_customer[MAX_ELEMENT];
	for (i = 0; i < MAX_ELEMENT; i++) {
		cafe_customer[i] = new int[CAFE_NUMBER];
	}
	string s;
	getline(fin, s);
	i = 0;
	while (fin) {
		for (j = 0; j < CAFE_NUMBER; j++) {
			cafe_customer[i][j] = s[j] - '0';
		}
		i++;
		getline(fin, s);
	}
	int cafe_score[CAFE_NUMBER];
	cout << "가게들의 평점을 입력\n 단, 아래 순서대로 입력하기!(0~5점 사이)\n";
	for (int i = 0; i < CAFE_NUMBER; i++) {
		wcout << i << ": " << cafe_snack[i].name << "\n";
	}
	for (int i = 0; i < CAFE_NUMBER; i++) {
		cin >> cafe_score[i];
	}

	graph_human cafe_example = graph_human(cafe_customer, i, CAFE_NUMBER, cafe_score);
	cafe_example.print_3_stores_cosine(cafe_snack);
	cafe_example.print_3_stores_PCC(cafe_snack);

	fin.close();
}

int main()
{
	wcout.imbue(std::locale("kor"));	// 출력
	wcin.imbue(std::locale("kor"));	// 출력
	wstring input;
	string input_expected_cost;
	wifstream wfin;
	wfin.imbue(std::locale("kor"));
	wfin.open("Restaurant_information.txt");
	if (!wfin.is_open()) {
		cout << "파일을 열 수 없습니다. \n" << std::endl;
		exit(EXIT_FAILURE);
	}
	int i=0,j=0;
	wfin >> input;
	while (wfin) {
		switch (j) {
		case 0: { store[i].name = input; j++; break; }
		case 1: { store[i].place = input; j++; break; }
		case 2: { store[i].range[0] = input; j++; break; }
		case 3: { store[i].range[1] = input; j++; break; }
		case 4: { input_expected_cost.assign(input.begin(), input.end()); store[i].expected_cost = atoi(input_expected_cost.c_str()); j++; break; }
		case 5: {store[i].time = input; j++; break; }
		case 6: {store[i].menu[0] = input; j++; break; }
		case 7: {store[i].menu[1] = input; j++; break; }
		case 8: {store[i].menu[2] = input; j++; break; }
		case 9: {store[i].menu_price[0] = input; j++; break; }
		case 10: {store[i].menu_price[1] = input; j++; break; }
		case 11: {store[i].menu_price[2] = input; j++; break; }
		default: {store[i].day_off = input; j = 0; i++; break; }
		}
		wfin >> input;
	}
	for (int k = 0; k < 321; k++) {
		if (store[k].range[0].compare(L"카페") == 0 || store[k].range[0].compare(L"간식") == 0) insert_max_heap(&c_s_temp, store[k]);
		else if (store[k].range[0].compare(L"술집") == 0) insert_max_heap(&bar_temp, store[k]);
		else insert_max_heap(&restaurant_temp, store[k]);
	}
	for (int i = RES_NUMBER; i>=0; i--) {
		if(i<=21) bar[i] = delete_max_heap(&bar_temp);
		if(i<=49) cafe_snack[i] = delete_max_heap(&c_s_temp);
		restaurant[i] = delete_max_heap(&restaurant_temp);
	}
	print_by_expected_cost();	// 1번 기능
	search();					// 2번 기능
	recommend_3_stores();		// 3번 기능
	recommend_by_grade_cafe_version();	// 4번 기능
	wfin.close();
	return 0;
}