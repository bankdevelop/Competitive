#include <stdio.h>
#include <stdlib.h>

typedef struct paths{
	int one;
	int two;
	int three;
	int four;
} Path;

void addMemPath(Path* memPath, char treasure, int length){
	if (treasure == '$'){
		if (length < (*memPath).one)
			(*memPath).one = length;
	}else if (treasure == '*'){
		if (length < (*memPath).two)
			(*memPath).two = length;
	}else if (treasure == '+'){
		if (length < (*memPath).three)
			(*memPath).three = length;
	}else if (treasure == '^'){
		if (length < (*memPath).four)
			(*memPath).four = length;
	}
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

int checkLength(Path* memPath, length){
	if ()
}

void DFSgo(char graph[][500], int h, int w, int sH, int sW, int** mem, Path* memPath, int length){
	if (length >= 20) return;
	if (sH >= h || sW >= w) return;
	if (sH <= 0 || sW <= 0) return;
	
	if (graph[sH][sW] == '$') 
		addMemPath(memPath, '$', length);
	else if (graph[sH][sW] == '*')
		addMemPath(memPath, '*', length);
	else if (graph[sH][sW] == '+')
		addMemPath(memPath, '*', length);
	else if (graph[sH][sW] == '^')
		addMemPath(memPath, '^', length);
	else if (graph[sH][sW] == '#') return;
	
	if (mem[sH][sW] == 1) return;
	mem = copyMem(mem, h, w);
	mem[sH][sW] = 1;
	
	DFSgo(graph, h, w, sH, sW-1, mem, memPath, length+1);
	DFSgo(graph, h, w, sH, sW+1, mem, memPath, length+1);
	DFSgo(graph, h, w, sH+1, sW, mem, memPath, length+1);
	DFSgo(graph, h, w, sH-1, sW, mem, memPath, length+1);
	freeMem(mem, h);
}

void DFS(char graph[][500], int h, int w, int sH, int sW, Path* memPath){
	int** remember = createMem(h+2, w+2);
	DFSgo(graph, h, w, sH, sW, remember, memPath, 0);
}

int main(){
	int h, w, startH=0, startW=0, break_loop=1;
	char graph[500][500];
	Path memPath;
	memPath.one = 500000, memPath.two = 500000;
	memPath.three = 500000, memPath.four = 500000;
	
	scanf("%d %d", &h, &w);
	for (int i=0; i<h; i++){
		scanf("%s", graph[i]);
	}
	
	for (startH=0; startH<h && break_loop; startH++)
		for (startW=0; startW<w && break_loop; startW++)
			if (graph[startH][startW]=='s')
				break_loop=0;
	
	DFS(graph, h, w, startH-1, startW-1, &memPath);
	
	if (memPath.one != 500000)
		printf("%d", memPath.one);
	else if (memPath.two != 500000)
		printf("%d", memPath.two);
	else if (memPath.three != 500000)
		printf("%d", memPath.three);
	else if (memPath.four != 500000)
		printf("%d", memPath.four);
	else printf("No Path!");
}