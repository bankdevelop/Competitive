#include <stdio.h>
#include <stdlib.h>

void solve3Square(int input, 
				 int* arr){
	
	int result, squareOne, squareTwo;

	for (int one=0; one<=input; one++){
		squareOne = one*one;
		if (squareOne > input) break;
		
		for (int two=one; two<=input; two++){
			squareTwo = two*two;
			if (squareTwo > input) break;
			
			for (int three=two; three<=input; three++){
				result = squareOne + squareTwo + three*three;
				
				if (result > input) break;
				if (result == input) {
					arr[0] = one;
					arr[1] = two;
					arr[2] = three;
					
					return;
				}
			}
		}
	}
}

void find3Square(int input, 
				int** output,
				int current_n){
					
	output[current_n] = malloc(sizeof(int)*3);
	output[current_n][0] = -1;
	
	solve3Square(input, output[current_n]);
}

int main(){
	int n, input;
	scanf("%d", &n);
	int** output = malloc(sizeof(int*)*n);
	
	for(int i=0; i<n; i++){
		scanf("%d", &input);
		find3Square(input, output, i);
	}
	
	for(int i=0; i<n; i++){
		if( output[i][0] == -1 ) printf("-1\n");
		else {
			printf("%d %d %d\n", output[i][0], 
								 output[i][1], 
								 output[i][2]);
		}
	}
}