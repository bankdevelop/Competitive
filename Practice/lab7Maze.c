#include <stdio.h>
#include <stdlib.h>

void addMemPath(int* memPath, int length){
	if (length < (*memPath)) (*memPath) = length;
}

int** createMem(int h, int w) {
	int** mem = malloc(sizeof(int*)*h);
	for (int i=0; i<h; i++) {
		mem[i] = malloc(sizeof(int)*w);
		for (int j=0; j<w; j++)
			mem[i][j] = 0;
	}
	return mem;
}

void freeMem(int** mem, int h){
	for (int i=0; i<h; i++)
		free(mem[i]);
	free(mem);
}

int** copyMem(int** target, int h, int w) {
	int** mem = createMem(h, w);
	for (int i=0; i<h; i++) {
		for (int j=0; j<w; j++)
			mem[i][j] = target[i][j];
	}
	return mem;
}

char searchChar(char graph[][500], char teasureNeed, int h, int w){
	for (int i=0; i<h; i++)
		for (int j=0; j<w; j++)
			if (graph[i][j] == teasureNeed) 
				return teasureNeed;
	return 'X';
}

void DFSgo(char graph[][500], int h, int w, int sH, int sW, int** mem, int* memPath, int length, char treasure){
	if (length > (*memPath)) return;
	if (sH >= h || sW >= w) return;
	if (sH <= 0 || sW <= 0) return;
	
	if (graph[sH][sW] == treasure)
		addMemPath(memPath, length);
	else if (graph[sH][sW] == '#') return;
	
	if (mem[sH][sW] == 1) return;
	mem[sH][sW] = 1;
	mem = copyMem(mem, h, w);
	
	DFSgo(graph, h, w, sH, sW-1, mem, memPath, length+1, treasure);
	DFSgo(graph, h, w, sH, sW+1, mem, memPath, length+1, treasure);
	DFSgo(graph, h, w, sH+1, sW, mem, memPath, length+1, treasure);
	DFSgo(graph, h, w, sH-1, sW, mem, memPath, length+1, treasure);
	freeMem(mem, h);
}

void DFS(char graph[][500], int h, int w, int sH, int sW, int* memPath, char treasure){
	int** remember = createMem(h+2, w+2);
	DFSgo(graph, h, w, sH, sW, remember, memPath, 0, treasure);
}

int main(){
	int h, w, startH=0, startW=0, break_loop=1;
	char graph[500][500], treasureSearh;
	char allTreasure[] = {'$', '*', '+', '^'};
	int memPath = 500000;
	
	scanf("%d %d", &h, &w);
	for (int i=0; i<h; i++){
		scanf("%s", graph[i]);
	}
	
	for (startH=0; startH<h && break_loop; startH++)
		for (startW=0; startW<w && break_loop; startW++)
			if (graph[startH][startW]=='s')
				break_loop=0;
	
	for (int i=0; i<4; i++){
		treasureSearh = searchChar(graph, allTreasure[i], h, w);
		if (treasureSearh != 'X'){
			DFS(graph, h, w, startH-1, startW-1, &memPath, treasureSearh);
			
			if (memPath != 500000) {
				printf("%d", memPath);
				break;
			}
		}
	}
	if (treasureSearh == 'X' || memPath == 500000) printf("No Path!");
}