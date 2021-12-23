#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SWAP(x,y,t)((t)=(x), (x)=(y), (y)=(t))
#define SIZE 100

void sort(int* arr, int size) {
	printf("Input: "); //Input 된 array를 출력
	for (int i = 0; i < size; i++) printf("%d ", arr[i]);
	printf("\n");
	int i, j, min, temp;
	for (i = 0; i < size - 1; i++) { //selection sort 진행
		min = i;
		for (j = i + 1; j < size; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
			SWAP(arr[i], arr[min], temp);
		}
	}
	printf("Sorted: "); //Sorting 한 결과 array를 출력
	for (int i = 0; i < size; i++) printf("%d ", arr[i]);
	printf("\n");
}

int main() {
	int n = SIZE;

	FILE* fp = fopen("lab1.data", "w+"); //lab1.data에 최악의 경우인 배열을 저장

	fprintf(fp, "%d\n", SIZE);
	for (int i = SIZE; i > 0; i--) {
		fprintf(fp, "%d\n", i);
	}
	fclose(fp); //읽기 전용으로 다시 열기 위해서 닫아준다.

	long rep = 0; //반복 실행 횟수를 세기 위함
	double duration = 0; //프로그램이 진행되는 시간을 확인, 평균 실행시간

	clock_t start = clock(); //시간 측정 시작
	int num;
	FILE* ifp = fopen("lab1.data", "r"); //lab1.data를 열어 selection sort를 실행
	do {
		rep++;
		fscanf(ifp, "%d", &num); //불러온 lab1.data에서 size를 읽고
		int* a = malloc(sizeof(int) * num); //그에 맞는 int 형 배열을 동적할당함
		for (int i = 0; i < num; i++) {
			fscanf(ifp, "%d", &a[i]); //배열의 요소를 읽음
		}
		sort(a, num); // sort 실행

		free(a);
		rewind(ifp); //다시 처음으로 돌아가 반복
	} while (clock() - start < 1000);
	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC; //시간측정 끝
	duration /= rep; //평균 실행 시간을 구함
	printf("%d\t%d\t%f\n", n, rep, duration); //반복 결과 출력

	fclose(ifp);
}