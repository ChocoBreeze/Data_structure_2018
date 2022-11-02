/*
15
4			20
1			  16  25
*/

#include<iostream>
struct TreeNode {
	int data;
	TreeNode *left, *right;
};
TreeNode n1 = { 1,NULL,NULL };
TreeNode n2 = { 4,&n1,NULL };
TreeNode n3 = { 16,NULL,NULL };
TreeNode n4 = { 25,NULL,NULL };
TreeNode n5 = { 20,&n3,&n4 };
TreeNode n6 = { 15,&n2,&n5 };
TreeNode *root = &n6;

void preorder(TreeNode *root) {
	if (root) {	//root!=NULL이면 수행
		std::cout << root->data <<" ";	// 노드 방문
		preorder(root->left);		// 왼쪽 서브트리
		preorder(root->right);		// 오른쪽 서브트리
	}
}

void inorder(TreeNode *root) {
	if (root) {	//root!=NULL이면 수행
		inorder(root->left);		// 왼쪽 서브트리
		std::cout << root->data << " ";	// 노드 방문
		inorder(root->right);		// 오른쪽 서브트리
	}
}

void postorder(TreeNode *root) {
	if (root) {	//root!=NULL이면 수행
		postorder(root->left);		// 왼쪽 서브트리
		postorder(root->right);		// 오른쪽 서브트리
		std::cout << root->data << " ";	// 노드 방문
	}
}

int main()
{
	inorder(root);
	std::cout << std::endl;
	preorder(root);
	std::cout << std::endl;
	postorder(root);
	std::cout << std::endl;
	return 0;
}