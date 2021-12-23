#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 1000

int failure[MAX_LENGTH];

void fail(char *pat){
	int i, j,n=strlen(pat); //반복문을 위한 i, j 
	failure[0]=-1; //첫 시작은 항상 -1이다.  
	for(j=1;j<n;j++){ //j는 pat의 index를 따라 증가한다. 
		i=failure[j-1]; //i는 이전칸의 failure를 받아온다. 이는 failure[j-1]에 해당하는 pat의 index를 불러오기 위함이다.
		while((pat[j]!=pat[i+1])&&(i>=0)) //뒤에서 pat[j]와 pat[i+1]을 비교할 때의 i를 결정해주기 위해서 조건을 검사한다. 
			i=failure[i]; //이로부터 계속해서 뒷걸음질 치는 fail의 모습을 만들 수 있다. 이 과정을 반복하지 않으면 kmp알고리즘의 효율성이 떨어진다. 
		if(pat[j]==pat[i+1]) //그리고 경우가 같은 경우를 만나면 failure를 1 증가하고 
			failure[j]=i+1;
		else failure[j]=-1; //아니면 -1로 정한다.  
	}
}

int pmatch(char *string, char *pat){
	int i=0,j=0;
	int lens =strlen(string);
	int lenp = strlen(pat);
	while (i<lens && j<lenp){ //길이까지 끝까지 탐색한다. 
		if (string[i]==pat[j]){
			i++; j++;
		}
		else if (j==0) i++;
		else j = failure[j-1]+1;	
	}
	return((j==lenp)?(i-lenp):-1); //j == lenp라는 것은 끝까지 돌았을 때 pat와 match되는 구간이 있었다는 이야기이다.
									//따라서 이 경우 i-lenp로 match되는 시작점을 반환한다. 아니면 -1. 
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
	
	fail(pat); //pat를 분석한다. 
	result = pmatch(string, pat); //string과 pat을 match 시킨다. 
	
	printf("%d", result);
}
