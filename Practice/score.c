#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Students{
	char name[100];
	int score;
} Student;

int main(){
	int n, sum=0;
	int min=300000, max=-300000;
	char min_name[100], max_name[100];
	scanf("%d", &n);
	Student stu[n];
	
	for(int i=0; i<n; i++){
		scanf("%s %d", stu[i].name, &stu[i].score);
		if(stu[i].score>max){
			max=stu[i].score;
			strcpy(max_name, stu[i].name);
		}else if(stu[i].score<min){
			min=stu[i].score;
			strcpy(min_name, stu[i].name);
		}
		sum+=stu[i].score;
	}
	
	//sort
	int j, k;
	for(j=0; j<n; j++){
		int stuMin = 300000, stuIndex=j;
		for(k=j; k<n; k++){
			if(stu[k].score<stuMin){
				stuMin = stu[k].score;
				stuIndex = k;
			}
		}
		//swap
		if(j!=stuIndex){
			Student temp = stu[j];
			stu[j] = stu[stuIndex];
			stu[stuIndex] = temp;
		}
	}
	
	//out
	int mean = sum/n;
	printf("Mean : %d\n", mean);
	printf("Max : %s Score : %d\n", max_name, max);
	printf("Mix : %s Score : %d\n", min_name, min);
	for(int p=n-1; p>=0; p--){
		if(stu[p].score<mean){
			printf("%s Score : %d\n", stu[p].name, stu[p].score);
		}
	}
}