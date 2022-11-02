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
	int heap_size;	// �� ����� ��
};

// �� ������ ���� �ӽ� �迭
HeapType restaurant_temp;
HeapType c_s_temp;
HeapType bar_temp;

void init(HeapType *h) {
	h->heap_size = 0;
}

void insert_max_heap(HeapType *h, store_info item) { //�ִ� ����
	int i = ++(h->heap_size);
	//Ʈ���� �Ž��� �ö� �θ���� ��
	while ((i != 1) && (item.expected_cost > h->heap[i / 2].expected_cost)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // �� ��� ����
}

store_info delete_max_heap(HeapType *h) {
	int parent, child;
	store_info item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ�� �� �� ū �ڽĳ�带 Ȱ��
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

//ù ��° ��� = ���ݼ����� ���� ���� ��쿡 ���� ���� ��� ������ ���� ���
void print_by_expected_cost() {
	int choice;
	cout << "ù ��° ���(���ݿ������� ���) : 1~3���� ���� �� �������ּ��� (1: �Ĵ� 2: ���� 3: ī�� �� ����) \n�Է� : ";
	cin >> choice;
	switch (choice) {
	case 1:		// �Ĵ�
		for (int i = 0; i < RES_NUMBER; i++) {
			wcout << i << "��° �����̸� : " << restaurant[i].name << " ���� ���� ��� : ";
			cout << restaurant[i].expected_cost << std::endl;
		}
		break;
	case 2:		// ����
		for (int i = 0; i < BAR_NUMBER; i++) {
			wcout << i << ": " << bar[i].name << " ���� ���� ��� : ";
			cout << bar[i].expected_cost << std::endl;
		}
		break;
	case 3:		// ī�� �� ����
		for (int i = 0; i < CAFE_NUMBER; i++) {
			wcout << i << ": " << cafe_snack[i].name << " ";
			cout << cafe_snack[i].expected_cost << std::endl;
		}
		break;
	}
}

//�� ��° ��� = �˻�
void search() {	
	int choice, choice_deeper;
	wstring str;
	cout << "�� ��° ���(�˻�) : 1~3���� ���� �� �������ּ��� (1: �Ĵ� 2: ���� 3: ī�� �� ����) \n�Է� : ";
	cin >> choice;
	cout << "���� �˻�\n : 1~3���� ���� �� �������ּ��� (1: ��ġ 2: ū ���� 3: ���� ����) \n�Է� : ";
	cin >> choice_deeper;
	switch (choice) {
	case 1:	// �Ĵ�
		switch (choice_deeper) {
		case 1:	// ��ġ
			cout << "�˻� ������ ��ġ : ������(���ſ���), ��ε�, ��ķ, ����, ����, ����, ���⵿, ���ϵ�, ������, û������\n";
			wcin >> str;
			for (int i = 0, j = 0; i < RES_NUMBER; i++)
				if (restaurant[i].place.compare(str) == 0) wcout << (++j) << "��° �����̸� : " << restaurant[i].name << std::endl;
			break;
		case 2:	// ū ����
			cout << "�˻� ������ ū ���� : ��Ʈ��, �н�, ����, ���, �ε�, �Ͻ�, �߽�, �ѽ�\n";
			wcin >> str;
			for (int i = 0, j = 0; i < RES_NUMBER; i++)
				if (restaurant[i].range[0].compare(str) == 0) wcout << (++j) << "��° �����̸� : " << restaurant[i].name << std::endl;
			break;
		case 3:	// ���� ����
			cout << "�˻� ������ ���� ���� : ȸ, �ܹ���, �ع�,����, ���屹, �ع�, �ֵ���, �Թڽ�����ũ, ������, ����, ����,ġŲ, �ѽĺ���, ǻ��,Ƣ��, ǻ��, �Ľ�Ÿ, ����, Ŀ��, Į����, ġŲ, �ʹ�, ä�ĺ���, ��ġȸ, ���, ���, �, ����, «��, ¥���, ��ȭ�丮, ��, ����, ��������, ��, ��Ż����, ����,���, ����, �쵿, �˹�, �ұ���, ���κ�, ����, �Ұ���, �Ұ��, ������, �������, ����ȸ, ������, ������ġ, �����, ����, ���ɵ�, �����屹, �����, �н�, �θ���, �δ��, �δ뺺��, ����, �����, ��, ���Ա�, ���, ������, �η�ġ��, ��������, ���ܹ�, ���θ�, ���,�쵿, ���, ���ö�, ����, �ø�, ��ٷο�, ��ġ�, ���, ��ī��, ����, ����, ����, ��â, ����,����, ���, ������, ������, ���ű��, ����\n";
			wcin >> str;
			for (int i = 0, j = 0; i < RES_NUMBER; i++)
				if (restaurant[i].range[1].compare(str) == 0) wcout << (++j) << "��° �����̸� : " << restaurant[i].name << std::endl;
			break;
		}
		break;
	case 2:	// ����
		switch (choice_deeper) {
		case 1:	// ��ġ
		case 2:
		case 3:
			cout << "������ ū ���ֿ� ���� ���ְ� ��� �������� �����ϹǷ� ��ġ�θ� �˻� �����մϴ�.\n";
			cout << "�˻� ������ ��ġ : ������(���ſ���), ����, ���⵿, ������\n";
			wcin >> str;
			for (int i = 0, j = 0; i < BAR_NUMBER; i++)
				if (bar[i].place.compare(str) == 0) wcout << (++j) << "��° �����̸� : " << bar[i].name << std::endl;
			break;
		}
		break;
	case 3:	 // ī��
		switch (choice_deeper) {
		case 1:	// ��ġ
			cout << "�˻� ������ ��ġ : ������, ������(���ſ���), ����ķ, �Ⱦϵ�, ��ķ, ����, ���⵿, ������\n";
			wcin >> str;
			for (int i = 0, j = 0; i < CAFE_NUMBER; i++)
				if (cafe_snack[i].place.compare(str) == 0) wcout << (++j) << "��° �����̸� : " << cafe_snack[i].name << std::endl;
			break;
		case 2:	// ū ����
			cout << "�˻� ������ ū ���� : ����, ī��\n";
			wcin >> str;
			for (int i = 0, j = 0; i < CAFE_NUMBER; i++)
				if (cafe_snack[i].range[0].compare(str) == 0) wcout << (++j) << "��° �����̸� : " << cafe_snack[i].name << std::endl;
			break;
		case 3:	// ���� ����
			cout << "�˻� ������ ���� ���� : ����,����Ŀ��, ������ġ, ���̽�ũ��, ī��, Ŀ��������, �׸�ī��\n";
			wcin >> str;
			for (int i = 0, j = 0; i < CAFE_NUMBER; i++)
				if (cafe_snack[i].range[1].compare(str) == 0) wcout << (++j) << "��° �����̸� : " << cafe_snack[i].name << std::endl;
			break;
		}
		break;
	}
}

//���� ���� ���絵 ���� - jaccard ���絵 
//�� ��° ��� = 1���� ���� �Է� �� �׿� ������ ���� ��õ
void recommend_3_stores() {
	int choice;
	Graph c_s = Graph(CAFE_NUMBER);
	c_s.cal_similarity(cafe_snack);
	Graph res = Graph(RES_NUMBER);
	res.cal_similarity(restaurant);
	Graph bar_ = Graph(BAR_NUMBER);
	bar_.cal_similarity(bar);
	cout << "�� ��° ���(�ϳ��� ���� �Է� �� ������ ���� ��õ)\n : 1~3���� ���� �� �������ּ��� (1: �Ĵ� 2: ���� 3: ī�� �� ����) \n�Է� : ";
	cin >> choice;
	switch (choice) {
	case 1:		// �Ĵ�
		for (int i = 0; i < RES_NUMBER; i++)
			wcout << i << ": " << restaurant[i].name << " ";
		cout << "\n�湮�ߴ� ���Ը� �ϳ� ��� �ּ���(����)  \n";
		cin >> choice;
		res.print_3_stores(choice, restaurant);
		break;
	case 2:		// ����
		for (int i = 0; i < BAR_NUMBER; i++)
			wcout << i << ": " << bar[i].name << " ";
		cout << "\n�湮�ߴ� ���Ը� �ϳ� ��� �ּ���(����)  \n";
		cin >> choice;
		bar_.print_3_stores(choice, bar);
		break;
	case 3:		// ī�� �� ����
		for (int i = 0; i < CAFE_NUMBER; i++)
			wcout << i << ": " << cafe_snack[i].name << " ";
		cout << "\n�湮�ߴ� ���Ը� �ϳ� ��� �ּ���(����)  \n";
		cin >> choice;
		c_s.print_3_stores(choice, cafe_snack);
		break;
	}
	c_s.~Graph();
	res.~Graph();
	bar_.~Graph();
}

// ī�信 ������ ����
// 50�� ���� ��Ͻ� ���� ������ ���� ���� ��õ
void recommend_by_grade_cafe_version() {
	cout << "�� ��° ���(��� ī����� ���� �Է� �� ������ ���� ��õ)(0~5 ������ ���ڷ� 50�� �Է����ּ���)\n�Է� : ";
	wcout.imbue(std::locale("kor"));	// ���
	wcin.imbue(std::locale("kor"));		// ���
	int i, j;
	ifstream fin;
	fin.open("cafe_simulation.txt");						// ���� �ڷ� - ����
	if (!fin.is_open()) {
		cout << "������ �� �� �����ϴ�. \n" << std::endl;
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
	cout << "���Ե��� ������ �Է�\n ��, �Ʒ� ������� �Է��ϱ�!(0~5�� ����)\n";
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
	wcout.imbue(std::locale("kor"));	// ���
	wcin.imbue(std::locale("kor"));	// ���
	wstring input;
	string input_expected_cost;
	wifstream wfin;
	wfin.imbue(std::locale("kor"));
	wfin.open("Restaurant_information.txt");
	if (!wfin.is_open()) {
		cout << "������ �� �� �����ϴ�. \n" << std::endl;
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
		if (store[k].range[0].compare(L"ī��") == 0 || store[k].range[0].compare(L"����") == 0) insert_max_heap(&c_s_temp, store[k]);
		else if (store[k].range[0].compare(L"����") == 0) insert_max_heap(&bar_temp, store[k]);
		else insert_max_heap(&restaurant_temp, store[k]);
	}
	for (int i = RES_NUMBER; i>=0; i--) {
		if(i<=21) bar[i] = delete_max_heap(&bar_temp);
		if(i<=49) cafe_snack[i] = delete_max_heap(&c_s_temp);
		restaurant[i] = delete_max_heap(&restaurant_temp);
	}
	print_by_expected_cost();	// 1�� ���
	search();					// 2�� ���
	recommend_3_stores();		// 3�� ���
	recommend_by_grade_cafe_version();	// 4�� ���
	wfin.close();
	return 0;
}