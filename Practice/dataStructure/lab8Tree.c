#include <stdio.h>
#include <stdlib.h>

typedef struct nodes{
	int parent;
	int child;
} Node;

int main(){
	int n, m, leaf_node = 0, have_child;
	
	scanf("%d", &n);
	scanf("%d", &m);
	
	Node node[m];
	if (m < n){
		for (int i=0; i<m; i++)
			scanf("%d %d", &node[i].parent, &node[i].child);
		
		for (int i=0; i<n; i++){
			have_child = 0;
			for (int j=0; j<m; j++){
				if (node[j].parent == (i+1)) have_child = 1;
			}
			
			if (!have_child) leaf_node++;
		}
		
		if (m==0) printf("1");
		else printf("%d", leaf_node);
	}
}