#include<iostream>
// ������ ����
struct TreeNode {
	int key;
	TreeNode *left, *right;
};

TreeNode * search_recursion(TreeNode *node, int key) { // 1. ���
	//�־��� Ű �� = ����� Ű --> ����� Ű ��ȯ
	//�־��� Ű �� < ����� Ű --> ���� ����Ʈ��
	//�־��� Ű �� > ����� Ű --> ������ ����Ʈ��
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key) return search_recursion(node->left, key);
	else return search_recursion(node->right, key);
}

TreeNode * search_iterator(TreeNode *node, int key) { // 2. �ݺ���
	while (node != NULL) {
		if (key == node->key) return node;
		else if (key < node->key) node = node->left;
		else node = node->right;
	 }
	return NULL;
}

void insert_node(TreeNode**root, int key) { // ���� ����
	TreeNode *p, *t;	// p�� �θ��� t�� ������
	TreeNode *n;		// n�� ���ο� ���
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
	// key�� ���� ��� t�� Ž�� ,p�� t�� �θ���
	p = NULL;
	t = *root;
	// key�� ���� ��� t�� Ž��
	while (t != NULL && t->key != key) {
		p = t;
		t = (key < t->key) ? t->left : t->right;
	}
	// Ž���� ����� ������ t�� NULL �̸� Ʈ�� �ȿ� key�� ����
	if (t == NULL) {
		std::cout << "key is not in the tree";
		return;
	}
	if (t->left == NULL && t->right == NULL) {// case 1: �ܸ���� 
		if (p != NULL) {
			// �θ����� �ڽĳ�带 NULL��
			if (p->left == t) p->left = NULL;
			else p->right = NULL;
		}
		else *root = NULL;	//�θ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
	}
	else if ((t->left == NULL) || (t->right == NULL)) {// case 2: �ϳ��� �ڽĸ� ������ ���
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) { // �θ����� �ڽ��ʵ带 child�� ����
			if (p->left == t) p->left = child;
			else p->right = child;
		}
		else *root = child;	// �θ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
	}
	else {// case 3:  �ΰ��� �ڽ��� ������ ���
		// ������ ����Ʈ������ �İ��ڸ� ã��
		// ������ ����Ʈ������ ���� ���� ��
		succ_p = t;
		succ = t->right;								// ���� succ=t->left;
		// �İ��ڸ� ã�Ƽ� ���� �������� ��
		while (succ->left != NULL) {					// succ ->right !=NULL
			succ_p = succ;							
			succ = succ->left;							// succ=succ->right;
		}
		// �ļ��ڿ� �θ� ����
		if (succ_p->left = succ) succ_p->left = succ->right;	// if(succ_p->right=succ) succ_p->right=succ->left;
		else succ_p->right = succ->right;						// else succ_p->left=succ->left;
		// �ļ��ڰ� ���� Ű ���� ���� ��忡 ����
		t->key = succ->key;
		// ������ �ļ��� ����
		t = succ;
	}
	//free(t); 
	//�����ϰ��� �� ��� �޸� ����
	delete t;
}