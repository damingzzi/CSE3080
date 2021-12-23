#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50

typedef enum { head, entry } tagfield;

typedef struct matrix_node* matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
} entry_node;

typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union {
		matrix_pointer next;
		struct entry_node entry;
	} u;
} matrix_node;

/* Global Variables */
matrix_pointer hdnode[MAX_SIZE];

/* Functions to be implemented by students */
matrix_pointer mread(FILE*); // file 에서 matrix 자료를 읽어 리스트에 저장한다.
void mwrite(matrix_pointer); // 행렬을 적절한 포맷 (2차원 행렬형태)으로 출력한다.
void merase(matrix_pointer*); // NULL parameter 인 경우 적절히 처리.

int main() {

	matrix_pointer a, b;
	FILE* fp_A, * fp_B;

	fp_A = fopen("A.txt", "r");
	fp_B = fopen("B.txt", "r");
	
	a = mread(fp_A);
	b = mread(fp_B);
	mwrite(a);
	mwrite(b);
	merase(&a);
	merase(&b);
	mwrite(a);
	mwrite(b);


	fclose(fp_A);
	fclose(fp_B);

	return 0;
}

matrix_pointer new_node() {
	matrix_pointer node = (matrix_pointer)malloc(sizeof(matrix_node));
	if (!node) {
		fprintf(stderr, "There is no available memory for allocation.\n");
		fprintf(stderr, "Program will be shutdown.\n");
		exit(0);
	}
	return node;
}

matrix_pointer mread(FILE* fp) {
	int numRows, numCols, numHeads, i, j;
	int value;
	matrix_pointer temp, last, node;

	fscanf(fp, "%d %d", &numRows, &numCols);

	numHeads = (numCols > numRows) ? numCols : numRows;

	node = new_node();
	node->u.entry.row = numRows;
	node->u.entry.col = numCols;

	if (!numHeads) node->right = node;
	else {
		for (i = 0; i < numHeads; i++) {
			temp = new_node();
			hdnode[i] = temp; hdnode[i]->tag = head;
			hdnode[i]->right = temp; hdnode[i]->u.next = temp;
		}
	}

	last = hdnode[0];
	int current_row = 0;
	/*for문 안에서 숫자를 하나씩 읽어주며 i=row, j=col, 받은 숫자=value로 두고 받기*/
	for (i = 0; i < numRows; i++) {
		for (j = 0; j < numCols; j++) {
			fscanf(fp, "%d", &value);
			if (!value) continue;
			if (current_row != i) {
				last->right = hdnode[current_row];
				current_row = i;
				last = hdnode[i];
			}
			temp = new_node();
			temp->tag = entry;
			temp->u.entry.row = i;
			temp->u.entry.col = j;
			temp->u.entry.value = value;
			last->right = temp;
			last = temp;
			hdnode[j]->u.next->down = temp;
			hdnode[j]->u.next = temp;
		}
	}
	last->right = hdnode[numRows - 1];
	for (int i = 0; i < numHeads; i++) {
		hdnode[i]->u.next->down = hdnode[i];
	}
	for (int i = 0; i + 1 < numHeads; i++) {
		hdnode[i]->u.next = hdnode[i + 1];
	}
	hdnode[numHeads - 1]->u.next = node;
	node->right = hdnode[0];
	return node;
}

void mwrite(matrix_pointer node) {
	int i, j;
	if (node == NULL) {
		printf("empty matrix\n");
		return;
	}
	matrix_pointer temp, head = node->right;
	for (i = 0; i < node->u.entry.row; i++) {
		head = head->right;
		for (j = 0; j < node->u.entry.col; j++) {
			if (j == head->u.entry.col) {
				printf("%d ", head->u.entry.value);
				head = head->right;
			}
			else printf("%d ", 0);
		}
		head = head->u.next;
		printf("\n");
	}
	printf("\n");
}

void merase(matrix_pointer* node) {
	matrix_pointer x, y, head = (*node)->right;
	int i;
	for (i = 0; i < (*node)->u.entry.row; i++) {
		y = head->right;
		while (y != head) {
			x = y; y = y->right; free(x);
		}
		x = head; head = head->u.next; free(x);
	}
	y = head;
	while (y != *node) {
		x = y; y = y->u.next; free(x);
	}
	free(*node); *node = NULL;
}