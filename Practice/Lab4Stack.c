#include <stdio.h>
#include <stdlib.h>

int main() {
	int stack[1000], temp[1000], n_stack=0, n_temp, num=0;
	long sum=0;
	
	while(1){
		scanf("%d", &num);
		if (num<0) break;
		stack[n_stack++] = num;
	}
	if (n_stack!=0){
		n_temp = n_stack;
		for (int j=0; j<n_stack; j++)
			temp[j] = stack[j];
		
		scanf("%d", &num);
		for (int i=0; i<num; i++) 
			sum+=stack[--n_stack];
		
		//output
		printf("|");
		for (int i=n_temp-1; i>=0; i--){
			printf(" %d", temp[i]);
		}
		printf(" |\n|");
		for (int i=n_stack-1; i>=0; i--){
			printf(" %d", stack[i]);
		}
		printf(" |\n");
		printf("%ld", sum);
	}
}