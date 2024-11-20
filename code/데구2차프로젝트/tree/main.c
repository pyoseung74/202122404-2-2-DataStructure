#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"


void main()
{
	tree_LL* TL;
	tree_A* TA;

	TL = CreateLListTree();
	TA = CreateArrayTree();

	InsertNodeA(TA,"hello");
	InsertNodeLL(TL, "hello");
	InsertNodeLL(TL, "apple");
	InsertNodeLL(TL, "valence");
	InsertNodeLL(TL, "a");

	PrintNodeA(TA, 0);
	PrintNodeLL(TL, 0);

}