#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#define UPPER_BOUND 90
#define LOWER_BOUND 10

#pragma region Structs

typedef struct Node* Next;
typedef struct Node {
	int _data;
	Next _left;
	Next _right;
} Node;

typedef struct Queue* After;

typedef struct Queue {
	int _data;
	After  _node;
}Queue;
#pragma endregion

#pragma region Function definitions

Next CreateNode(int);
Next InsertNode(Next, int);
int ReplaceWithSum(Next);
int SumSubtrees(Next);
Next InsertRandom(Next,After);
int RNG();
int InOrder(Next);
int Pop(After );
int Push(After, int);
int WriteInFile(After);
#pragma endregion


#pragma region Functions

Next CreateNode(int data) {
	Next node = (Next)(malloc(sizeof(Node)));
	node->_data = data;
	node->_left = NULL;
	node->_right = NULL;
	return node;
}

Next InsertNode(Next Parent, int data) {
	if (Parent == NULL ) {
		Parent = CreateNode(data);
		return Parent;
	}
	if (data > Parent->_data) {
		Parent->_left = InsertNode(Parent->_left, data);
	}
	else if (data < Parent->_data) {
		Parent->_right = InsertNode(Parent->_right, data);
	}
	return Parent;
}

int ReplaceWithSum(Next root) {
	if (root == NULL) {
		return NULL;
	}
	root->_data = SumSubtrees(root->_left) + SumSubtrees(root->_right);

	ReplaceWithSum(root->_left);
	ReplaceWithSum(root->_right);

	return EXIT_SUCCESS;
}

int SumSubtrees(Node* root) {
	if (root == NULL) {
		return 0;
	}
	return root->_data + SumSubtrees(root->_left) + SumSubtrees(root->_right);
}

Next InsertRandom(Next root) {

	Next node = InsertNode(root, RNG());

	return node;
}

int RNG() {

	int randomNumber = rand();

	return randomNumber % (UPPER_BOUND - LOWER_BOUND - 1) + LOWER_BOUND + 1;
}

int InOrder(Next Root, After Head)
{
	if (Root == NULL) return;

	InOrder(Root->_left, Head);
	Push(Head, Root->_data);
	InOrder(Root->_right, Head);

	return EXIT_SUCCESS;
}
int Pop(After Head) {
	After temp = Head->_node;
	Head->_node = Head->_node->_node;
	return temp->_data;
}
int Push(After Head, int data) {
	while (Head->_node != NULL) {
		Head = Head->_node;
	}

	After tmp = (After)(malloc(sizeof(struct Queue)));
	tmp->_data = data;
	tmp->_node = NULL;

	Head->_node = tmp;

	return EXIT_SUCCESS;
}

int WriteInFile(After Head) {
	FILE* f;
	int num;
	f = fopen("Nodeovi.txt", "w");
	if (f == NULL) {
		return EXIT_FAILURE;
	}
	while (Head->_node != NULL)
	{
		num = Pop(Head);
		fprintf(f, "%d ", num);
	}
	fclose(f);
}

#pragma endregion


int main(void) {
	Next Root = NULL;
	Queue Head = {._data=0,._node=NULL};
	srand(time(NULL));

	/*
	// a)	i b)
	Root = InsertNode(Root, 2);
	InsertNode(Root, 5);
	InsertNode(Root, 7);
	InsertNode(Root, 8);
	InsertNode(Root, 11);
	InsertNode(Root, 1);
	InsertNode(Root, 4);
	InsertNode(Root, 2);
	InsertNode(Root, 3);
	InsertNode(Root, 7);
	replaceWithSum(Root);*/


	
	//c)
	Root = InsertRandom(Root);
	InsertRandom(Root);
	InsertRandom(Root);
	InsertRandom(Root);
	InsertRandom(Root);
	InsertRandom(Root);
	InsertRandom(Root);
	InsertRandom(Root);
	InOrder(Root, &Head);
	WriteInFile(&Head);

	
	return EXIT_SUCCESS;

}