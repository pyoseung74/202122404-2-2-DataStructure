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
	// 현재는 비어 있는 트리에 루트를 채워주는 상황.
	if (strcmp(t->data[0], "") == 0)
		strcpy(t->data[0], str);
}



void InsertNodeLL(tree_LL* t, char* str)
{
	treenode* temp;
	temp = (treenode*)malloc(sizeof(treenode));
	temp->left = NULL;
	temp->right = NULL;
	strcpy(temp->data, str);

	// 현재는 비어 있는 트리에 루트를 채워주는 상황.
	if (t->root == NULL)
		t->root = temp;

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

}
