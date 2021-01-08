#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (256)

struct _dir;
typedef struct _dir* positionD;
typedef struct _dir {
	char name[MAX];
	positionD sibling;
	positionD child;

}Dir;

struct _stack;
typedef struct _stack* positionS;
typedef struct _stack{
	positionD dir;
	positionS next;

}Stack;

int menu(positionD,positionS);
positionD createDir(char*);
void push(positionD,positionS);
positionD pop(positionD,positionS);
int deleteAll(positionD);
void insert(positionD);
void printDir(positionD);
positionD find(positionD, positionS, char*);
void location(positionD);
void printPath(positionD, positionD);

int main() {

	positionD root = createDir("C:");
	Stack head;
	head.next = NULL;
	head.dir = NULL;

	push(root, &head);
	menu(root, &head);


	return EXIT_SUCCESS;
}

positionD createDir(char *dirName) {
	positionD K;
	K = (positionD)malloc(sizeof(Dir));
	if (!K)
		printf("Wrong memory allocation!");
	strcpy(K->name, dirName);
	K->child = NULL;
	K->sibling = NULL;
	return K;
}

int menu(positionD root,positionS head) {
	positionD current = root;
	
	int option;

	while (1) {

		char name[MAX];

		printf("\nPress:\n");
		printf("0)For end of program\n");
		printf("1)For making new directory\n");
		printf("2)For printing current directory data\n");
		printf("3)To find directory\n");
		printf("4)To print current location\n");
		printf("5)To go backwards \n");
		printf("6)Show complete path\n");

		scanf("%d", &option);

		switch (option) {
		case 0:
			deleteAll(current);
			return EXIT_SUCCESS;
			break;


		case 1:
			insert(current);
			break;

		case 2:
			printDir(current);
			break;

		case 3:
			printf("Insert directory name that you are looking for: ");
			scanf("%s", name);

			current = find(root, &head, name);

			if (current != NULL) {
				printf("Directory exists, its path:\n");
				printPath(root, current);
			}
			else
				printf("It doesn't exist!\n");
			break;

		case 4:
			location(current);
			break;

		case 5:
			current = pop(current,head);
			location(current);
			break;
		case 6:
			printPath(root, current);
			break;

		default:
			printf("Insert numbers from 0-6 only!\n");
			break;
		}
	}

}

void insert(positionD current) {

	positionD prev = current;

	positionD K;
	char dirName[MAX];

	printf("Insert new dir name: ");
	scanf("%s", dirName);

	K = createDir(dirName);

	if (current->child == NULL) {

		K->sibling = current->child;
		current->child = K;

		return 0;
	}

	current = current->child;

	if (strcmp(current->name, K->name) > 0) {

		K->sibling = current;
		prev->child = K;

		return;
	}


	while (current != NULL && strcmp(current->name, K->name) < 0) {

		prev = current;
		current = current->sibling;

	}

	K->sibling = prev->sibling;
	prev->sibling = K;

}

void printDir(positionD current) {

	printf("In this directory %s\n", current->name);
	current = current->child;

	if (NULL == current) {
		printf("Directory is empty!\n");
		return 0;
	}

	while (current != NULL) {
		printf("%s\n", current->name);
		current = current->sibling;
	}

}

positionD find(positionD current, positionS head, char* name) {
	if (current == NULL) {

		printf("Directory doesn't exist\n");
		return NULL;
	}

	if (current != NULL && current->child != NULL && strcmp(current->name, name) != 0) {

		push(current, head);
		current = find(current->child, head, name);
	}
	if (current != NULL && current->sibling != NULL && strcmp(current->name, name) != 0) {

		current = find(current->sibling, head, name);
	}

	if (current != NULL && strcmp(current->name, name) == 0) {
		return current;
	}
	else
		return NULL;

}

void location(positionD current) {
	if (current != NULL)
		printf("Current location: %s\n", current->name);
}

int deleteAll(positionD current) {
	if (NULL == current)
		return EXIT_SUCCESS;

	deleteAll(current->child);
	deleteAll(current->sibling);
	free(current);

	return EXIT_SUCCESS;
}

void push(positionD current, positionS head) {

	positionS q;
	q = (positionS)malloc(sizeof(Stack));

	if (NULL == q) {
		printf("Wrong allocation\n!");
		return;
	}

	q->dir = current;
	q->next = head->next;
	head->next = q;

}

positionD pop(positionD current, positionS head) {
	positionD q;
	positionS temp;

	if (head->next == NULL) {
		printf("Stack is empty you can't go more backwards!\n");
		return current;
	}

	q = head->next->dir;

	temp = head->next;
	head->next = temp->next;
	free(temp);

	return q;

}

void printPath(positionD root, positionD current) {
	
	printf("%s\\ ", root->name);
	root = root->child;

	while (root != NULL && root != current->child) {
		printf("%s\\ ", root->name);
		root = root->child;
	}

	printf("\n");



}