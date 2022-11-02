/*
			G
		 C     F
		A B   D E
*/
#include<iostream>
const int TRUE = 1;
const int FALSE = 0;

struct TreeNode {
	int data;
	TreeNode *left, *right;
	int is_thread;		// ���� ������ ��ũ�� �������̸� TRUE ���������� �ڽ��� �ƴ� ���� ���� --> TRUE
};

TreeNode n1 = { 'A',NULL,NULL,TRUE };
TreeNode n2 = { 'B',NULL,NULL,TRUE };
TreeNode n3 = { 'C',&n1,&n2,FALSE };
TreeNode n4 = { 'D',NULL,NULL,TRUE };
TreeNode n5 = { 'E',NULL,NULL,FALSE };
TreeNode n6 = { 'F',&n4,&n5,FALSE };
TreeNode n7 = { 'G',&n3,&n6,FALSE };
TreeNode *exp_ = &n7;

TreeNode *find_successor(TreeNode *p) {
	// q�� p�� ������ ������
	TreeNode *q = p->right;
	if (q == NULL || p->is_thread == TRUE) return q;	// ������ �����Ͱ� NULL�̰ų� �������̸� ������ ������ ��ȯ
	while (q->left != NULL) q = q->left;	// ���� ������ �ڽ��̸� �ٽ� ���� ���� ���� �̵�
	return q;
}

void thread_inorder(TreeNode *t) {
	TreeNode *q;
	q = t;
	while (q->left) q = q->left;	// ���� �������� �̵�
	do {
		std::cout << char(q->data) << " ";		// ������ ���
		q = find_successor(q);				// �ļ��� �Լ� ȣ��
	} while (q != NULL);
}

int main()
{
	//Thread ����
	n1.right = &n3; // A �� �������� C��
	n2.right = &n7; // B �� �������� G��
	n4.right = &n6; // D �� �������� F��
	// Thread�� ���� inorder traversal
	thread_inorder(exp_);
}