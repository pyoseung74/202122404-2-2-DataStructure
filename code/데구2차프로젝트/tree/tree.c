#include "tree.h"

tree_A* CreateArrayTree()
{
	tree_A* tree= (tree_A*)malloc(sizeof(tree_A));
	tree->maxindex = (int)pow(2, MAXDEGREE + 1);
	
	tree->data = (char**)malloc(sizeof(char*) * tree->maxindex);
	for (int i = 0; i < tree->maxindex; i++)
	{
		tree->data[i] = (char*)malloc(sizeof(char) * STRINGSIZE);
		strcpy(tree->data[i], "");
	}

	return tree;
}

tree_LL* CreateLListTree()
{
	tree_LL* tree = (tree_LL*)malloc(sizeof(tree_LL));
	tree->root = NULL;

	return tree;
}


void InsertNodeA(tree_A* t, char* str)
{
	int index = 1;
	// 현재는 비어 있는 트리에 루트를 채워주는 상황.
	if (strcmp(t->data[index], "") == 0)
		strcpy(t->data[index], str);
	else
	{
		// cmp 함수는 앞에 있는 애가 사전적으로 먼저 오면 -1 리턴
		// 계속 움직여야함.. index 만 바꿔주면 됨
		// t->data[index] vs str
		// strcmp(t->data[index], str) == -1 >> str이 오른쪽에 붙어야함
		while(1)
		{
			if (strcmp(t->data[index], str) == -1)
			{
				index = index * 2 + 1;
			}
			else if (strcmp(t->data[index], str) == 1)
			{
				index = index * 2;
			}
			else
			{
				return;
			}
			if (strcmp(t->data[index], "") == 0)
				break;
		}
		strcpy(t->data[index], str);
	}
}


void InsertNodeLL(tree_LL* t, char* str)
{
	treenode* temp;
	treenode* tracking = t->root;
	temp = (treenode*)malloc(sizeof(treenode));
	temp->left = NULL;
	temp->right = NULL;
	strcpy(temp->data, str);

	// 현재는 비어 있는 트리에 루트를 채워주는 상황.
	if (t->root == NULL)
		t->root = temp;
	else
	{
		while (1) {
			if (strcmp(tracking->data, str) == -1)
			{
				if (tracking->right == NULL)
				{
					tracking->right = temp;
					break;
				}
				tracking = tracking->right;
			}
			else if (strcmp(tracking->data, str) == 1)
			{
				if (tracking->left == NULL)
				{
					tracking->left = temp;
					break;
				}
				tracking = tracking->left;
			}
		}
	}
}

void DeleteNodeA(tree_A* t, char* str)
{
}
void DeleteNodeLL(tree_LL* t, char* str)
{
}


void PrintNodeA(tree_A* t, int type)
{

}
void PrintNodeLL(tree_LL* t, int type)
{
	treenode* temp = ;
	PreOrder(temp);
}
void PreOrder(treenode* t)
{
	if (t == NULL)
		return;
	printf("%s, ", t->data);
	PreOrder(t->left);
	PreOrder(t->right);
}

void CheckBSTA(tree_A* t)
{

}

void CheckBSTLL(tree_LL* t)
{

}
