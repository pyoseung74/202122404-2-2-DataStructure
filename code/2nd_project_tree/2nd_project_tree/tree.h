	#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define STRINGSIZE 30
#define MAXDEGREE 6

// 배열 형태로 저장하는 트리
typedef struct tree_Array
{
	char** data;
	int maxindex;
}tree_A;

// 리스트 트리를 위한 노드
typedef struct treenode
{
	char data[STRINGSIZE];
	struct treenode* left;
	struct treenode* right;
}treenode;

// 리스트 형태로 저장하는 트리
typedef struct tree_LinkedList
{
	treenode* root;
}tree_LL;

// 연결 리스트 기반 레벨 순회용 큐
typedef struct _queue
{
	treenode* data[200];
	int front, rear;
} Queue;

// 트리를 배열 형태로 생성
tree_A* CreateArrayTree();

// 트리를 연결리스트 형태로 생성
tree_LL* CreateLListTree();

// 각 형태의 트리에서 str 을 추가
void InsertNodeA(tree_A *t,char *str);
void InsertNodeLL(tree_LL *t,char* str);

// 각 형태의 트리에서 str 을 삭제
void DeleteNodeA(tree_A* t, char* str);
void DeleteNodeLL(tree_LL* t, char* str);

// 각 트리 형태를 변경하여 리턴
tree_A* List2Array(tree_LL* t);
tree_LL* Array2List(tree_A* t);

//type 0: pre, 1: in,  2: post, 3: level
void PrintNodeA(tree_A* t, int type);
void PrintNodeLL(tree_LL* t, int type);

// t의 형태를 출력
void CheckBSTA(tree_A* t);
void CheckBSTLL(tree_LL* t);

// num 번째로 나오는 문자열 리턴
char* FindnthA(tree_A* t, int num);
char* FindnthLL(tree_LL* t, int num);

// str을 찾아가는 과정을 출력
void FindPathA(tree_A* t, char* str);
void FindPathLL(tree_LL* t, char* str);

// 메모리 해제 함수 (배열 기반 트리, 연결 리스트 기반 트리)
void DestroyArrayTree(tree_A* t);
void DestroyLListTree(tree_LL* t);