#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SWAP(a, b, type) do{ type temp; temp = a; a = b; b = temp; }while (0)

void sort(float** data, int feature);
int weight_cal(float** data, float* weight);

int t_num, d_num, feature, c_num;
int i, j, res;

int main() {
	FILE* dfp = fopen("data.txt", "r");
	FILE* tfp = fopen("test.txt", "r");
	FILE* ofp = fopen("output.txt", "w");

	res = fscanf(tfp, "%d", &t_num);
	if (res == EOF) exit(0);
	res = fscanf(dfp, "%d %d", &d_num, &feature);
	if (res == EOF) exit(0);
	float** data;
	data =(float **) malloc(sizeof(float*) * d_num);
	for (i = 0; i < d_num; i++) {
		data[i] = (float *)malloc(sizeof(float) * (feature+2));
	}//data ������ ���缭 data array�� �غ�, data[i][feature]���� class, data[i][feature+1]���� distance

	for (i = 0; i < d_num; i++) {
		for (j = 0; j < feature+1; j++) {
			res = fscanf(dfp, "%f", &data[i][j]);
			if (res == EOF) break;
		}
		if (c_num < data[i][feature]) c_num = (int)data[i][feature];
	}//feature�� class �о��

	float* weight;
	if ((weight = (float*)malloc(sizeof(float) * (c_num + 1))) == NULL) {
		exit(0);
	}

	float* test;
	test = (float *)malloc(sizeof(float) * feature);
	
	while (t_num--) {
		for (i = 0; i < feature; i++) {
			res = fscanf(tfp, "%f", &test[i]);
			if (res == EOF) break; 
		}//�м��� �׽�Ʈ ���̽��� �о��

		for (i = 0; i < d_num; i++) {
			float dist = 0;
			for (j = 0; j < feature; j++) {
				float temp = test[j] - data[i][j]; 
				dist += temp*temp;
			}
			dist = sqrt(dist);
			data[i][feature+1] = dist;
		}

		sort(data, feature); //k���� ������ ������ ���� distance�� �������� sorting�� ����.
		
		int output = weight_cal(data, weight);
		fprintf(ofp, "%d\n", output);
	}
	
	fclose(dfp);
	fclose(tfp);
	fclose(ofp);
	free(test);
	free(data);
	free(weight);

	return 0;
}

void sort(float** data, int feature) {
	int min, i, j;
	for (i = 0; i < d_num-1; i++) {
		min = i;
		for (j = i+1; j < d_num; j++) {
			if (data[j][feature+1] <= data[min][feature+1]) {
				min = j;
			}
			SWAP(data[i], data[min], float*);
		}
	}
}

int weight_cal(float** data, float *weight) {
	int c = 0, i;
	float d = 0;
	
	for (i = 0; i <= c_num; i++) {
		weight[i] = 0;
	}

	for (i = 0; i < 5; i++) {
		c = (int)data[i][feature];
		d = 1 / data[i][feature+1];
		weight[c] += d;
	}
	int max = 0;
	for (i = 1; i <= c_num; i++) {
		if (weight[i] > weight[max]) max = i;
	}
	
	return max;
}
