#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _bTree;
typedef struct _bTree * Position;
typedef struct _bTree {
	int el;
	Position Lchild;
	Position Rchild;

}bTree;


Position createEl(int);
int menu();
Position findMaxLeft(Position);




int main()
{
	bTree Root;
	Root.Lchild = NULL;
	Root.Rchild = NULL;

	menu();

	return EXIT_SUCCESS;
}

Position createEl(int el) {
	Position K;
	K = (Position)malloc(sizeof(bTree));
	if (!K)
		printf("Memory allocation failed!");

	K->el = el;
	K->Lchild = NULL;
	K->Rchild = NULL;

	return K;
}

Position findMaxLeft(Position current) {





}


