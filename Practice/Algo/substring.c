#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int n;
	scanf("%d", &n);
	
	char* arr[n];
	int size_arr[n];
	for (int i=0; i<n; i++){
	    arr[i] = malloc(sizeof(char)*105);
		scanf("%s", arr[i]);
	}
	
	//collect length to array
	for (int i=0; i<n; i++)
		size_arr[i] = strlen(arr[i]);
	
	//insertion sort
	for (int i=1; i<n; i++){
		for (int j=i; j>0; --j){
			if (size_arr[j] < size_arr[j-1]){
				char* tmp = arr[j];
				int tmp_size = size_arr[j];
				
				arr[j] = arr[j-1];
				size_arr[j] = size_arr[j-1];
				
				arr[j-1] = tmp;
				size_arr[j-1] = tmp_size;
			}
		}
	}
	
	//compare substring
	int isYES = 1;
	for (int i=1; i<n; i++){
		int current=0;
		int noSubstring=1;
		int size = strlen(arr[i]);
		int target = strlen(arr[i-1]);
		
		for (int j=0; j<size; j++){
			if (arr[i-1][current] == arr[i][j])
				current++;
			else
				current=0;
			
			if (current == target){
				noSubstring=0;
				break;
			}
		}
		
		if (noSubstring) {
			isYES=0;
			break;
		}
	}
	
	if (isYES){
		printf("YES\n");
		for (int i=0; i<n; i++)
			printf("%s\n", arr[i]);
	}else printf("NO");
}