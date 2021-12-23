#include<stdio.h>
#include<stdlib.h>

typedef struct threadedTree* threadedPointer;
typedef struct threadedTree {
	short int leftThread;
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread;
}threadedTree;

void construct_tree(threadedPointer tree);
threadedPointer insucc(threadedPointer tree);
void tinorder(threadedPointer tree);
void insertRight(threadedPointer s, threadedPointer r);
void insert(threadedPointer s, char data);

int main()
{
	/* initialize a head node */
	threadedPointer root = (threadedPointer)malloc(sizeof(threadedTree));
	root->data = 0;
	root->leftChild = root ;
	root->rightChild = root;
	root->leftThread = 0;
	root->rightThread = 0;

	/* construct a given tree */
	construct_tree(root);
	insert(root->leftChild->rightChild, 'E');
	insert(root->leftChild->leftChild->rightChild, 'F');
	insert(root->leftChild->leftChild, 'G');
	tinorder(root);
	//getchar();
	return 0;
}

void construct_tree(threadedPointer tree)
{
	threadedPointer temp, temp_root;

	temp_root = tree;
	/* insert node 'A' to the left of the head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = 1;
	temp->leftChild = temp->rightChild = temp;
	temp->data = 'A';

	temp_root->leftChild = temp;
	temp_root->leftThread = 0;

	temp_root = tree->leftChild;
	/* insert node 'B' to the left of the temp_head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->rightThread = temp->leftThread = 1;
	temp->leftChild = tree;
	temp->rightChild = temp;
	temp->data = 'B';

	temp_root->leftChild = temp;
	temp_root->leftThread = 0;

	/* insert node 'C' to the right of the temp_head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = 1;
	temp->leftChild = temp_root;
	temp->rightChild = tree;
	temp->data = 'C';

	temp_root->rightChild = temp;
	temp_root->rightThread = 0;

	temp_root = temp_root->leftChild;
	/* insert node 'D' to the right of the temp_head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = 1;
	temp->leftChild = temp_root;
	temp->rightChild = tree->leftChild;
	temp->data = 'D';

	temp_root->rightChild = temp;
	temp_root->rightThread = 0;
}

threadedPointer insucc(threadedPointer tree)
{ //find the inorder sucessor of tree in a threaded binary tree
	threadedPointer temp;
	temp = tree->rightChild;
	if (!tree->rightThread) {
		while (!temp->leftThread) {
			temp = temp->leftChild;
		}
	}
	return temp;
}

void tinorder(threadedPointer tree)
{ //traverse the threaded binary tree inorder 
	threadedPointer temp = tree;
	temp = insucc(temp);
	printf("%c", temp->data);
	for (;;) {
		temp = insucc(temp);
		if (temp == tree) break;
		printf("%3c", temp->data);
	}
	printf("\n");
}

void insert(threadedPointer s, char data)
{
	threadedPointer temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->data = data;
	insertRight(s, temp);
}

void insertRight(threadedPointer s, threadedPointer r)
{ //insert r as the right child of s
	threadedPointer temp;
	r->rightChild = s->rightChild;
	r->rightThread = s->rightThread;
	r->leftChild = s;
	r->leftThread = 1;
	s->rightChild = r;
	s->rightThread = 0;
	if (!r->rightThread) {
		temp = insucc(r);
		temp->leftChild = r;
	}
}