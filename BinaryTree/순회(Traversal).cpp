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
	if (root) {	//root!=NULL�̸� ����
		std::cout << root->data <<" ";	// ��� �湮
		preorder(root->left);		// ���� ����Ʈ��
		preorder(root->right);		// ������ ����Ʈ��
	}
}

void inorder(TreeNode *root) {
	if (root) {	//root!=NULL�̸� ����
		inorder(root->left);		// ���� ����Ʈ��
		std::cout << root->data << " ";	// ��� �湮
		inorder(root->right);		// ������ ����Ʈ��
	}
}

void postorder(TreeNode *root) {
	if (root) {	//root!=NULL�̸� ����
		postorder(root->left);		// ���� ����Ʈ��
		postorder(root->right);		// ������ ����Ʈ��
		std::cout << root->data << " ";	// ��� �湮
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