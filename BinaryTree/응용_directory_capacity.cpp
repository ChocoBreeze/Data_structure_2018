#include<iostream>

/*
				0
		   100	   50
		500	200
*/

struct TreeNode {
	int data;
	TreeNode *left, *right;
};

int calc_direc_size(TreeNode *root) {
	int left_size, right_size;
	if (!root) return 0; //root==NULL
	else {
		left_size = calc_direc_size(root->left);	// 왼쪽 사이즈
		right_size = calc_direc_size(root->right);	// 오른쪽 사이즈
		return (root->data + left_size + right_size);
	}
}

int main()
{
	TreeNode n5 = { 200,NULL,NULL };
	TreeNode n4 = { 500,NULL,NULL };
	TreeNode n3 = { 100,&n4,&n5 };
	TreeNode n2 = { 50,NULL,NULL };
	TreeNode n1 = { 0,&n2,&n3 };

	std::cout << calc_direc_size(&n1)<< std::endl;
}