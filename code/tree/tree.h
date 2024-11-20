#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define STRINGSIZE 30
#define MAXDEGREE 6


typedef struct tree_Array
{
	char** data;
	int maxindex;
}tree_A;


typedef struct treenode
{
	char data[STRINGSIZE];
	struct treenode* left;
	struct treenode* right;
}treenode;

typedef struct tree_LinkedList
{
	treenode* root;
}tree_LL;


tree_A* CreateArrayTree();
tree_LL* CreateLListTree();

void InsertNodeA(tree_A *t,char *str);
void InsertNodeLL(tree_LL *t,char* str);

void DeleteNodeA(tree_A* t, char* str);
void DeleteNodeLL(tree_LL* t, char* str);


tree_A* List2Array(tree_LL* t);
tree_LL* Array2List(tree_A* t);

//type 0: pre, 1: in,  2: post, 3: level
void PrintNodeA(tree_A* t, int type);
void PrintNodeLL(tree_LL* t, int type);

void CheckBSTA(tree_A* t);
void CheckBSTLL(tree_LL* t);

char* FindnthA(tree_A* t, int num);
char* FindnthLL(tree_LL* t, int num);

void FindPathA(tree_A* t, char* str);
void FindPathLL(tree_LL* t, char* str);

