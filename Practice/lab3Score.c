#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Students{
	char name[50];
	int point;
} Student;

int max_int(int num1, int num2){
	if(num1>num2) return num1;
	return num2;
}

int main(){
	
	char name[50];
	int point, n_input=0;
	Student stu[163];
	long sum=0;
	int min=3000, max=-3000;
	
	while(1){
		scanf("%s", name);
		if (!strcmp(name, "stop!")) break;
		scanf("%d", &point);
		
		strcpy(stu[n_input].name, name);
		stu[n_input++].point = point;
		sum+=point;
		
		if (point>max) max=point;
		if (point<min) min=point;
	}
	
	//selection sort
	int index_max, i;
	for(i=0; i<n_input; i++){
		index_max=i;
		for(int j=i; j<n_input; j++){
			int length_index_max = strlen(stu[index_max].name);
			int length_index_j = strlen(stu[j].name);
			for(int k=0; k<max_int(length_index_max, length_index_j); k++){
				if(length_index_j<=k && length_index_max>k){
					break;
				}
				if(length_index_j>k && length_index_max<=k){
					index_max=j;
					break;
				}
				
				if(stu[j].name[k]>stu[index_max].name[k]){
					index_max=j;
					break;
				}else if(stu[j].name[k]<stu[index_max].name[k]) break;
			}
		}
		if (index_max!=i){
			Student temp=stu[index_max];
			stu[index_max] = stu[i];
			stu[i] = temp;
		}
	}
	
	//output
	if(n_input>0){
		printf("Min: %d\n", min);
		printf("Max: %d\n", max);
		printf("Mean: %.3f\n\n", (float)sum/n_input);
		
		for(int p=n_input-1; p>=0; p--)
			printf("%s : %d\n", stu[p].name, stu[p].point);
	}
}