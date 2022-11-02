#include<iostream>

struct TreeNode {
	int data;
	TreeNode *left, *right;
};

void main()
{
	TreeNode *n1, *n2, *n3;

	n1 = new TreeNode;
	n2 = new TreeNode;
	n3 = new TreeNode;

	n1->data = 10;
	n1->left = n2;
	n1->right = n3;

	n2->data = 20;
	n2->left = NULL;
	n2->right = NULL;

	n3->data = 30;
	n3->left = NULL;
	n3->right = NULL;

	delete n1;
	delete n2;
	delete n3;
}