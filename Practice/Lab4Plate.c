#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int output[500][500], output_length[500];
	char command[15];
	int stack[500], n_stack=0, n_output=0, num;
	
	do{
		scanf("%s", command);
		if (!strcmp("push", command)){
			scanf("%d", &num);
			stack[n_stack++] = num;
			for(int i=0; i<n_stack; i++){
				output[n_output][i]=stack[i];
			}
			output_length[n_output++] = n_stack;
		} else if (!strcmp("pop", command)) {
			--n_stack;
			for(int i=0; i<n_stack; i++){
				output[n_output][i]=stack[i];
			}
			output_length[n_output++] = n_stack;
		}
			
	}while(strcmp("end!", command));
	
	//output
	for(int i=0; i<n_output; i++){
		printf("|");
		for(int j=output_length[i]-1; j>=0; j--){
			printf(" %d", output[i][j]);
		}
		printf(" |\n");
	}
}