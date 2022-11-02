/*
		+
	*		+		
   1 4    16 25

*/

#include<iostream>

struct TreeNode {
	int data;
	TreeNode * left, *right;
};

TreeNode n1 = { 1,NULL,NULL };
TreeNode n2 = { 4,NULL,NULL };
TreeNode n3 = { '*',&n1,&n2 };
TreeNode n4 = { 16,NULL,NULL };
TreeNode n5 = { 25,NULL,NULL };
TreeNode n6 = { '+',&n4,&n5 };
TreeNode n7 = { '+',&n3,&n6 };
TreeNode *exp_ = &n7;

int evaluate(TreeNode *root) {
	if (!root) return 0;		// root ==NULL
	if (!(root->left) && !(root->right)) return root->data;	// root==leaf node
	else {
		int op1 = evaluate(root->left);	//왼쪽트리
		int op2 = evaluate(root->right);	//오른쪽트리
		switch(root->data) {
			case '+': return op1 + op2;
			case '-': return op1 - op2;
			case '*': return op1 * op2;
			case '/': return op1 / op2;
		}
	}
	return 0;
}

int main()
{
	std::cout << evaluate(exp_);
	return 0;
}