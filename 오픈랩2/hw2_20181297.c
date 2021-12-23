#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 1000

int failure[MAX_LENGTH];

void fail(char *pat){
	int i, j,n=strlen(pat); //�ݺ����� ���� i, j 
	failure[0]=-1; //ù ������ �׻� -1�̴�.  
	for(j=1;j<n;j++){ //j�� pat�� index�� ���� �����Ѵ�. 
		i=failure[j-1]; //i�� ����ĭ�� failure�� �޾ƿ´�. �̴� failure[j-1]�� �ش��ϴ� pat�� index�� �ҷ����� �����̴�.
		while((pat[j]!=pat[i+1])&&(i>=0)) //�ڿ��� pat[j]�� pat[i+1]�� ���� ���� i�� �������ֱ� ���ؼ� ������ �˻��Ѵ�. 
			i=failure[i]; //�̷κ��� ����ؼ� �ް����� ġ�� fail�� ����� ���� �� �ִ�. �� ������ �ݺ����� ������ kmp�˰����� ȿ������ ��������. 
		if(pat[j]==pat[i+1]) //�׸��� ��찡 ���� ��츦 ������ failure�� 1 �����ϰ� 
			failure[j]=i+1;
		else failure[j]=-1; //�ƴϸ� -1�� ���Ѵ�.  
	}
}

int pmatch(char *string, char *pat){
	int i=0,j=0;
	int lens =strlen(string);
	int lenp = strlen(pat);
	while (i<lens && j<lenp){ //���̱��� ������ Ž���Ѵ�. 
		if (string[i]==pat[j]){
			i++; j++;
		}
		else if (j==0) i++;
		else j = failure[j-1]+1;	
	}
	return((j==lenp)?(i-lenp):-1); //j == lenp��� ���� ������ ������ �� pat�� match�Ǵ� ������ �־��ٴ� �̾߱��̴�.
									//���� �� ��� i-lenp�� match�Ǵ� �������� ��ȯ�Ѵ�. �ƴϸ� -1. 
}

int main(){
	FILE *ifp;
	int temp, result=0;
	char string[MAX_LENGTH], pat[MAX_LENGTH];
	
	ifp=fopen("kmp.txt", "r");
	if (ifp==NULL){
		printf("FILE OPEN ERROR\n");
		return 1;
	}
		
	temp=fscanf(ifp, "%s", &string);
	temp=fscanf(ifp, "%s", &pat);
	
	fail(pat); //pat�� �м��Ѵ�. 
	result = pmatch(string, pat); //string�� pat�� match ��Ų��. 
	
	printf("%d", result);
}
