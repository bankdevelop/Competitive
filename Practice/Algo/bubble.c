#include <stdio.h>
#include <stdlib.h>

void print_arr(unsigned int* arr, int n){
	for (int i=0; i<n; i++){
		if (i+1 == n)
			printf("%u\n", arr[i]);
		else
			printf("%u, ", arr[i]);
	}
}

int main(){
	int n=0;
	scanf("%d", &n);
	
	unsigned int arr[n];
	for (int i=0; i<n; i++){
		scanf("%u", &arr[i]);
	}
	print_arr(arr, n);
	
	//bubble sort
	for (int j=0; j<n; j++){
		for (int k=0; k+1<n; k++){
			if (arr[k] > arr[k+1]){
				unsigned int tmp = arr[k];
				arr[k] = arr[k+1];
				arr[k+1] = tmp;

				print_arr(arr, n);
			}
		}
	}
}
