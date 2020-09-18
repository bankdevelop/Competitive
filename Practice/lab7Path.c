#include <stdio.h>
#include <stdlib.h>

typedef struct edges{
	int start;
	int destination;
} Edge;

int travel(Edge edge, int start){
	if (edge.start == start) 
		return edge.destination;
	if (edge.destination == start) 
		return edge.start;
	return -1;
}

int get_destination(Edge arr[], int point, int n, int mem[]){
	for (int i=0; i<n; i++){
		int result = travel(arr[i], point);
		if (result != -1 && mem[result] == 1) 
			continue;
		if(result != -1) {
			mem[result] = 1;
			return result;
		}
	}
	return -1;
}

int main(){
	int n, n_edge, remember[500];
	Edge arr_edge[500], edge_input;
	for (int i=0; i<500; i++) remember[i]=0;
	
	scanf("%d", &n);
	scanf("%d", &n_edge);
	for (int i=0; i<n_edge; i++){
		scanf("%d %d", &arr_edge[i].start, &arr_edge[i].destination);
	}
	
	scanf("%d %d", &edge_input.start, &edge_input.destination);
	int current_point = edge_input.start, destination;
	remember[current_point] = 1;
	
	while( current_point != edge_input.destination ){
		destination = get_destination(arr_edge, current_point, n_edge, remember);
		if (destination == -1) break;
		current_point = destination;
	}
	
	if (destination == -1)
		printf("False");
	else
		printf("True");
}