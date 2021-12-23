#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fileRead();
double calEntrophy();
double findNumeric();

int ntrain, num, cat;
int t_case, t_num, t_cat;

typedef struct leaf {
	int* numeric;
	int* categoric;
	int c;
	struct leaf* lpoint;
}leaf;

leaf* root;
leaf* test;

int main() {
	fileRead();

	
}

void fileRead() {
	FILE* train = fopen("train.txt", "r");
	int a;
	a=fscanf("%d %d %d", &ntrain, &num, &cat);
	
	root = (leaf*)malloc(sizeof(leaf));
	leaf* temp = root;
	int cnt = 0;
	while (cnt < ntrain) {
		leaf* temp1 = (leaf*)malloc(sizeof(leaf));
		temp1->numeric = (int*)malloc(sizeof(int) * num);
		temp1->categoric = (int*)malloc(sizeof(int) * cat);
		for (int i = 0; i < num; i++) {
			a= fscanf(train, "%d", &(temp1->numeric[i]));
		}
		for (int i = 0; i < cat; i++) {
			a= fscanf(train, "%d", &(temp1->categoric[i]));
		}
		a= fscanf(train, "%d", &temp1->c);
		root->lpoint = temp1;
		root = root->lpoint;
		cnt++;
	}
	root = temp;
	
	FILE* t_txt = fopen("test.txt", "r");
	a=fscanf(t_txt, "%d %d %d", &t_case, &t_num, &t_cat);
	cnt = 0;
	test = (leaf*)malloc(sizeof(leaf));
	while (cnt < test) {
		leaf* temp2 = (leaf*)malloc(sizeof(leaf));
		temp2->numeric = (int*)malloc(sizeof(int) * t_num);
		temp2->categoric = (int*)malloc(sizeof(int) * t_cat);
		for (int i = 0; i < t_num; i++) {
			a=fscanf(t_txt, "%d", &(temp2->numeric[i]));
		}
		for (int i = 0; i < t_cat; i++) {
			a=fscanf(t_txt, "%d", &(temp2->categoric[i]));
		}
		cnt++;
	}

	fclose(t_txt);
	fclose(train);
}

double calEntrophy(leaf * r, int i) {
	double sum = 0;
	double entrophy;
	double en[4] = { 0, };
	double a;
	int cnt=0;
	leaf* temp = r;
	while(r->lpoint !=NULL) {
		sum += r->c;
		r = r->lpoint;
		cnt++;
	}
	r = temp;

	a = sum / cnt;
	entrophy = -((1 - a) * log(1 - a)) - (a * log(a));
	
	temp = r;
	while (r->lpoint != NULL) {
		if ((r->categoric[i] == 0) && (r->c == 0)) en[0]++;
		else if ((r->categoric[i] == 0) && (r->c == 1)) en[1]++;
		else if ((r->categoric[i] == 1) && (r->c == 0)) en[2]++;
		else if ((r->categoric[i] == 1) && (r->c == 1)) en[3]++;
		r = r->lpoint;
	}
	r = temp;

	a = en[0] / cnt;

	
	
}