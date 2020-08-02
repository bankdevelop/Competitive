#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Students{
	char name[50];
	int point;
} Student;

int main(){
	
	char name[50];
	int point, n_input=0;
	Student stu[100];
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
			for(int k=0; k<strlen(stu[index_max].name); k++){
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
	printf("Min: %d\n", min);
	printf("Max: %d\n", max);
	printf("Mean: %.3f\n\n", (float)sum/n_input);
	
	for(int p=n_input-1; p>=0; p--)
		printf("%s : %d\n", stu[p].name, stu[p].point);
}