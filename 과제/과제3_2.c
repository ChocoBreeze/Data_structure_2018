#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct treenode {
	int score;
	int student_number;
	char name[20];
	struct treenode*left, *right;
}treenode;


int score_insert(int i)
{
	if (i<50) return 49 - i;
	else return i;
}

void insert_node(treenode**root, int score, treenode*tree1)   //삽입 
{
	treenode *p, *t;
	treenode *n;
	t = *root;
	p = NULL;

	while (t != NULL)
	{
		if (score == t->score) return;
		p = t;
		if (score<p->score) t = p->left;
		else t = p->right;
	}

	n = tree1;
	n->left = n->right = NULL;

	if (p != NULL)
		if (score<p->score) p->left = n;
		else p->right = n;
	else *root = n;

}

void delete_node(treenode**root, int score)
{
	treenode *p, *child, *succ, *succp, *t;  //key를 갖는 노드 t를 탐색,t의 부모는 p 
	p = NULL;
	t = *root;
	while (t != NULL&&t->score != score)
	{
		p = t;
		t = (score<p->score) ? p->left : p->right;
	}
	if (t == NULL)                        //key가 없으면 return  
		return;

	if ((t->left == NULL) && (t->right == NULL)) //t가 단말노드인 경우 
	{
		if (p != NULL)
		{
			if (p->left == t) p->left = NULL;
			else p->right = NULL;
		}
		else *root = NULL;
	}

	else if ((t->left == NULL) || (t->right == NULL))  //t가 하나의 자식만 가질경우 
	{
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL)
		{
			if (p->left == t) p->left = child;
			else p->right = child;
		}
		else *root = child;
	}


	else    //t가 두개의 자식 가질경우 
	{
		succp = t;
		succ = t->right;
		while (succ->left != NULL)
		{
			succp = succ;
			succ = succ->left;
		}
		if (succp->left == succ)
			succp->left = succ->right;
		else
			succp->right = succ->right;
		t->score = succ->score;
		strcpy(t->name, succ->name);
		t->student_number = succ->student_number;
		t = succ;

	}
	free(t);

}

treenode *search(treenode*node, int score)   //탐색 
{
	while (node != NULL)
	{
		if (score == node->score)
		{
			printf("%d", node->score);
			return node;
		}
		else if (score<node->score)
		{
			printf("%d->", node->score);
			node = node->left;
		}
		else
		{
			printf("%d->", node->score);
			node = node->right;
		}
	}
	return NULL;
}

void preorder(treenode*root)
{
	if (root)
	{
		printf("%d %d %s\n", root->score, root->student_number, root->name);
		preorder(root->left);
		preorder(root->right);
	}
}


int main()
{
	int i = 0;
	treenode *tree = NULL;
	treenode *tree1[100];
	FILE*fp = fopen("student_info.txt", "r");
	for (i = 0; i<100; i++)
	{
		tree1[i] = (treenode*)malloc(sizeof(treenode));
		fscanf(fp, "%d\t%[^\n]s", &(tree1[i]->student_number), tree1[i]->name);
		tree1[i]->score = score_insert(i);
		insert_node(&tree, tree1[i]->score, tree1[i]);
	}
	printf("<전위순회>\n");
	preorder(tree);
	printf("\n\n<13찾기>\n");
	search(tree, 13);
	printf("\n\n<단말노드 0 삭제>\n");
	delete_node(&tree, 0);
	preorder(tree);
	printf("\n\n<자식노드1개노드 10 삭제>\n");
	delete_node(&tree, 10);
	preorder(tree);
	printf("\n\n<자식노드2개노드 49 삭제>\n");
	delete_node(&tree, 49);
	preorder(tree);
	return 0;
}