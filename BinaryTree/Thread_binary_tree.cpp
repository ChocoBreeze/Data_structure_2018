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
	int is_thread;		// 만약 오른쪽 링크가 스레드이면 TRUE 오른쪽으로 자식이 아닌 것이 연결 --> TRUE
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
	// q는 p의 오른쪽 포인터
	TreeNode *q = p->right;
	if (q == NULL || p->is_thread == TRUE) return q;	// 오른쪽 포인터가 NULL이거나 스레드이면 오른쪽 포인터 반환
	while (q->left != NULL) q = q->left;	// 만약 오른쪽 자식이면 다시 가장 왼쪽 노드로 이동
	return q;
}

void thread_inorder(TreeNode *t) {
	TreeNode *q;
	q = t;
	while (q->left) q = q->left;	// 가장 왼쪽으로 이동
	do {
		std::cout << char(q->data) << " ";		// 데이터 출력
		q = find_successor(q);				// 후속자 함수 호출
	} while (q != NULL);
}

int main()
{
	//Thread 설정
	n1.right = &n3; // A 의 오른쪽을 C로
	n2.right = &n7; // B 의 오른쪽을 G로
	n4.right = &n6; // D 의 오른쪽을 F로
	// Thread를 통한 inorder traversal
	thread_inorder(exp_);
}