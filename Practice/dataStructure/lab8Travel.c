#include <stdio.h>
#include <stdlib.h>

typedef struct nodes{
	int parent;
	int child;
} Node;

int getChild(Node node[], int parent, int m, int* mem){
	for (int i=0; i<m; i++){
		if(mem[node[i].child]!=0) continue;
		if(node[i].parent == parent){
			mem[node[i].child] = 1;
			return node[i].child;
		}
	}
	return -1;
}

void travelGo(Node node[], int m, int* mem, int travel) {
	if(travel==-1) return;
	int nextTravel = travel;
	for(int i=0; i<m; i++){
		nextTravel = getChild(node, travel, m, mem);
		if (nextTravel==-1) break;
		travelGo(node, m, mem, nextTravel);
	}
	printf("%d ", travel);
}

void travelBefore(Node node[], int m, int* mem, int travel) {
	if(travel==-1) return;
	int nextTravel = travel;
	printf("%d ", travel);
	for(int i=0; i<m; i++){
		nextTravel = getChild(node, travel, m, mem);
		if (nextTravel==-1) break;
		travelBefore(node, m, mem, nextTravel);
	}
}

int main(){
	int root, m;
	
	scanf("%d", &m);
	scanf("%d", &root);
	
	Node node[m];
	int mem[500], mem2[500];
	for (int i=0; i<500; i++){
		mem[i]=0;
		mem2[i]=0;
	}
	
	for (int i=0; i<m; i++)
		scanf("%d %d", &node[i].parent, &node[i].child);
	
	travelBefore(node, m, mem, root);
	printf("\n");
	travelGo(node, m, mem2, root);
}