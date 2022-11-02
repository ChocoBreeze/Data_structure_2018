#include<iostream>
// 메인이 없다
struct TreeNode {
	int key;
	TreeNode *left, *right;
};

TreeNode * search_recursion(TreeNode *node, int key) { // 1. 재귀
	//주어진 키 값 = 노드의 키 --> 노드의 키 반환
	//주어진 키 값 < 노드의 키 --> 왼쪽 서브트리
	//주어진 키 값 > 노드의 키 --> 오른쪽 서브트리
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key) return search_recursion(node->left, key);
	else return search_recursion(node->right, key);
}

TreeNode * search_iterator(TreeNode *node, int key) { // 2. 반복문
	while (node != NULL) {
		if (key == node->key) return node;
		else if (key < node->key) node = node->left;
		else node = node->right;
	 }
	return NULL;
}

void insert_node(TreeNode**root, int key) { // 삽입 연산
	TreeNode *p, *t;	// p는 부모노드 t는 현재노드
	TreeNode *n;		// n은 새로운 노드
	t = *root;
	p = NULL;

	while (t != NULL) {
		if (key = t->key) return;
		p = t;
		if (key < t->key) t = t->left;
		else t = t->right;
	}

	// n = (TreeNode *)malloc(sizeof(TreeNode));
	// if(n==NULL) exit(1);
	n = new TreeNode;
	n->key = key;
	n->left = n->right = NULL;

	if (p != NULL) {
		if (key < p->key) p->left = n;
		else p->right = n;
	}
	else *root = n;
}

void delete_node(TreeNode **root, int key) {
	TreeNode *p, *child, *succ, *succ_p, *t;
	// key를 가진 노드 t를 탐색 ,p는 t의 부모노드
	p = NULL;
	t = *root;
	// key를 가진 노드 t를 탐색
	while (t != NULL && t->key != key) {
		p = t;
		t = (key < t->key) ? t->left : t->right;
	}
	// 탐색이 종료된 시점에 t가 NULL 이면 트리 안에 key가 없음
	if (t == NULL) {
		std::cout << "key is not in the tree";
		return;
	}
	if (t->left == NULL && t->right == NULL) {// case 1: 단말노드 
		if (p != NULL) {
			// 부모노드의 자식노드를 NULL로
			if (p->left == t) p->left = NULL;
			else p->right = NULL;
		}
		else *root = NULL;	//부모노드가 NULL이면 삭제되는 노드가 루트
	}
	else if ((t->left == NULL) || (t->right == NULL)) {// case 2: 하나의 자식만 가지는 경우
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) { // 부모노드의 자식필드를 child로 변경
			if (p->left == t) p->left = child;
			else p->right = child;
		}
		else *root = child;	// 부모노드가 NULL이면 삭제되는 노드가 루트
	}
	else {// case 3:  두개의 자식을 가지는 경우
		// 오른쪽 서브트리에서 후계자를 찾음
		// 오른쪽 서브트리에서 가장 작은 값
		succ_p = t;
		succ = t->right;								// 왼쪽 succ=t->left;
		// 후계자를 찾아서 가장 왼쪽으로 감
		while (succ->left != NULL) {					// succ ->right !=NULL
			succ_p = succ;							
			succ = succ->left;							// succ=succ->right;
		}
		// 후속자와 부모를 연결
		if (succ_p->left = succ) succ_p->left = succ->right;	// if(succ_p->right=succ) succ_p->right=succ->left;
		else succ_p->right = succ->right;						// else succ_p->left=succ->left;
		// 후속자가 가진 키 값을 현재 노드에 복사
		t->key = succ->key;
		// 원래의 후속자 삭제
		t = succ;
	}
	//free(t); 
	//삭제하고자 한 노드 메모리 해제
	delete t;
}