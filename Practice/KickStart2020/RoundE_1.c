#include <stdio.h>
#include <stdlib.h>

void LCA(int* result, int arr[], int m){
	int max = 0;
		
	int period = 1000000;
	int count = 1;
	for (int k=0; k<m; k++){
		int thisPeriod = arr[k]-arr[k+1];
		if (period == 1000000) period = thisPeriod;
		if (thisPeriod == period) count++;
		else {
			count = 1;
			period = 1000000;
			if (k+2 < m)
				if (arr[k+1]-arr[k+2] == thisPeriod)
					count++;
		}
    if (count > max) max = count;
	}
	(*result) = max<2?2:max;
}

int main(){
	int n, m;
	scanf("%d", &n);
	
	int result[n];
	for (int i=0; i<n; i++){
		scanf("%d", &m);
		int arr[m];
		
		for (int j=0; j<m; j++){
			scanf("%d", &arr[j]);
		}
		
		LCA(&result[i], arr, m); // longest contiguous arithmetic
	}
	
	for (int i=0; i<n; i++){
		printf("Case #%d: %d\n", i+1, result[i]);
	}
}