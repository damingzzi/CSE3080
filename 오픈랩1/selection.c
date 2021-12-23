#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SWAP(x,y,t)((t)=(x), (x)=(y), (y)=(t))
#define SIZE 100

void sort(int* arr, int size) {
	printf("Input: "); //Input �� array�� ���
	for (int i = 0; i < size; i++) printf("%d ", arr[i]);
	printf("\n");
	int i, j, min, temp;
	for (i = 0; i < size - 1; i++) { //selection sort ����
		min = i;
		for (j = i + 1; j < size; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
			SWAP(arr[i], arr[min], temp);
		}
	}
	printf("Sorted: "); //Sorting �� ��� array�� ���
	for (int i = 0; i < size; i++) printf("%d ", arr[i]);
	printf("\n");
}

int main() {
	int n = SIZE;

	FILE* fp = fopen("lab1.data", "w+"); //lab1.data�� �־��� ����� �迭�� ����

	fprintf(fp, "%d\n", SIZE);
	for (int i = SIZE; i > 0; i--) {
		fprintf(fp, "%d\n", i);
	}
	fclose(fp); //�б� �������� �ٽ� ���� ���ؼ� �ݾ��ش�.

	long rep = 0; //�ݺ� ���� Ƚ���� ���� ����
	double duration = 0; //���α׷��� ����Ǵ� �ð��� Ȯ��, ��� ����ð�

	clock_t start = clock(); //�ð� ���� ����
	int num;
	FILE* ifp = fopen("lab1.data", "r"); //lab1.data�� ���� selection sort�� ����
	do {
		rep++;
		fscanf(ifp, "%d", &num); //�ҷ��� lab1.data���� size�� �а�
		int* a = malloc(sizeof(int) * num); //�׿� �´� int �� �迭�� �����Ҵ���
		for (int i = 0; i < num; i++) {
			fscanf(ifp, "%d", &a[i]); //�迭�� ��Ҹ� ����
		}
		sort(a, num); // sort ����

		free(a);
		rewind(ifp); //�ٽ� ó������ ���ư� �ݺ�
	} while (clock() - start < 1000);
	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC; //�ð����� ��
	duration /= rep; //��� ���� �ð��� ����
	printf("%d\t%d\t%f\n", n, rep, duration); //�ݺ� ��� ���

	fclose(ifp);
}