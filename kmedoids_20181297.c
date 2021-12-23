#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#define MAXINUM_ITERTATION 1000

typedef struct Node {
	double* feature;
	struct Node* pointer;
}Node;

Node* head;
Node ** medoids;

void calCluster();
void cleanMed();
int changeMed(int i);
int N, K, F, t, cnt, flag;

int main() {
	FILE* ifp = fopen("input.txt", "r");
	FILE* ofp = fopen("output.txt", "w");

	t = fscanf(ifp, "%d %d %d", &N, &F, &K);

	//input 파일을 읽어오며 head라는 이름의 linked list를 작성
	head = (Node*)malloc(sizeof(Node));
	Node* temp = head;
	while (cnt < N) {
		Node* newnode = (Node*)malloc(sizeof(Node));
		newnode->feature = (double*)malloc(sizeof(double) * F);
		newnode->pointer = NULL;
		for (int i = 0; i < F; i++) {
			t = fscanf(ifp, "%lf", &(newnode->feature[i]));
		}
		head->pointer = newnode;
		head = head->pointer;
		cnt++;
	}
	head = temp;

	//K개의 medoid를 배열로 만든다.
	srand(1000);
	medoids = (Node **)malloc(sizeof(Node) * K);
	for (int i = 0; i < K; i++) {
		medoids[i] = (Node*)malloc(sizeof(Node));
		int j = rand() % N;		
		temp = head;
		head = head->pointer;
		for (int k = 0; k < j; k++) {
			head = head->pointer;
		}
		medoids[i]->feature = head->feature;
		medoids[i]->pointer = NULL;
		head = temp;
	}

	//1000이하로 distance를 계산 및 cluster분류, medoids 재설정을 반복한다.
	cnt = MAXINUM_ITERTATION;
	while (cnt--) {
		calCluster();
		for (int i = 0; i < K; i++) {
			flag += changeMed(i);
		}
		if (flag == K) { 
			
			break;
		}
		flag = 0;
	}
	//fprintf를 이용하여 output.txt 작성
	
	for (int i = 0; i < K; i++) {
		fprintf(ofp, "%d\n", i);
		temp = medoids[i]->pointer;
		while (temp != NULL) {
			fprintf(ofp, "[ ");
			for (int j = 0; j < F; j++) {
				fprintf(ofp, "%.10lf ", temp->feature[j]);
			}
			fprintf(ofp, "]\n");
			temp = temp->pointer;
		}
	}

	Node* t = NULL;
	while (temp != NULL) {
		t = temp;
		temp = temp->pointer;
		free(t);
	}
	free(head);
	cleanMed();
	free(medoids);
	fclose(ifp);
	fclose(ofp);
}

void calCluster(){
	int min =0;
	
	cleanMed();
	Node* temp1 = head->pointer;
	Node** tempMed = (Node**)malloc(sizeof(Node) * K);
	for (int i = 0; i < K; i++) {
		tempMed[i] = medoids[i];
	}
	while (temp1 != NULL) {
		double distance=0, minDist = DBL_MAX;
		for (int i = 0; i < K; i++) {
			distance = 0;
			for (int j = 0; j < F; j++) {
				distance += (tempMed[i]->feature[j] - temp1->feature[j]) * (tempMed[i]->feature[j] - temp1->feature[j]);
			}
			distance = sqrt(distance);
			if (minDist > distance) {
				minDist = distance;
				min = i;
			}
		}
		//data를 medoids[min]에 추가
		Node* newMed = (Node *)malloc(sizeof(Node));
		newMed->feature = temp1->feature;
		newMed->pointer = NULL;
		medoids[min]->pointer = newMed;
		medoids[min] = newMed;
		temp1 = temp1->pointer;
	}
	for (int i = 0; i < K; i++) {
		medoids[i] = tempMed[i];
	}
}

void cleanMed() {
	for (int i = 0; i < K; i++) {
		Node* tempMed = medoids[i]->pointer;
		if (medoids[i]->pointer == NULL) {
			continue;
		}
		Node* t = NULL;
		while (tempMed != NULL) {
			t = tempMed;
			tempMed = tempMed->pointer;
			free(t);
		}
	}
}

int changeMed(int i) {
	Node* tempMed = medoids[i]->pointer; //탐색하는 노드
	Node* minMed = medoids[i]->pointer; //최솟값을 저장하는 노드
	int ret = 0;
	double minDist = DBL_MAX;
	while (tempMed != NULL) {
		Node* temp2 = medoids[i]->pointer;
		double distance = 0 ;
		while (temp2 != NULL) {
			for (int j = 0; j < F; j++) {
				distance += (tempMed->feature[j] - temp2->feature[j]) * (tempMed->feature[j] - temp2->feature[j]);
			}
			temp2 = temp2->pointer;
		}
		distance = sqrt(distance);
		if (minDist > distance) {
			minDist = distance;
			minMed = tempMed;
		}
		tempMed = tempMed->pointer;
	}
	for (int j = 0; j < F; j++) {
		if (medoids[i]->feature[j] != minMed->feature[j]) {
			ret = 0;
		}
		else ret = 1;
	}
	medoids[i]->feature = minMed->feature;
	return ret;
}