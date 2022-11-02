/*

15
4   20
1   16  25

*/
#include<iostream>
#include<cstdlib>
#include<algorithm>

struct TreeNode {
	int data;
	TreeNode *left, *right;
};

//전체 노드 수 반환
int get_node_count(TreeNode *node) {
	int cnt = 0;
	if (node) cnt = 1 + get_node_count(node->left) + get_node_count(node->right);	// 1은 루트 노드
	return cnt;
}

//단말 노드 수 반환
int get_leaf_node(TreeNode* node) {
	int cnt = 0;
	if (node) {
		if (!(node->left) && !(node->right)) return 1;	// 단말노드면 return 1
		else cnt = get_leaf_node(node->left) + get_leaf_node(node->right);
	}
	return cnt;
}

//높이 반환
int get_height(TreeNode *node) {
	int height = 0;
	if (node) height = 1 + std::max(get_height(node->left), get_height(node->right));	// c는 max 없음
	return height;
}

TreeNode n1 = { 1,NULL,NULL };
TreeNode n2 = { 4,&n1,NULL };
TreeNode n3 = { 16,NULL,NULL };
TreeNode n4 = { 25,NULL,NULL };
TreeNode n5 = { 20,&n3,&n4 };
TreeNode n6 = { 15,&n2,&n5 };
TreeNode *root = &n6;

int main()
{
	std::cout << "All node #: " << get_node_count(root) << "\n";
	std::cout << "Leaf node #: " << get_leaf_node(root) << "\n";
	std::cout << "Height of tree: " << get_height(root) << "\n";
	return 0;
}