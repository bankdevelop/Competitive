#include <stdio.h>
#include <stdlib.h>

int main(){
	int w, h, n, q;
	scanf("%d %d %d %d", &w, &h, &n, &q);

	int** arr = malloc(sizeof(int*)*h);
	for (int i=0; i<h; i++){
		arr[i] = malloc(sizeof(int)*w);
		for (int j=0; j<w; j++)
			arr[i][j] = 0;
	}
	
	for (int i=0; i<n; i++){
		int r, c;
		scanf("%d %d", &r, &c); // r = w , c = h
		
		arr[c][r] = -100;
		
		if (c+1<h){
			if (r+1<w)
				++arr[c+1][r+1];
			if (r-1>=0)
				++arr[c+1][r-1];
			++arr[c+1][r];
		}
		if (c-1>=0){
			if (r+1<w)
				++arr[c-1][r+1];
			if (r-1>=0)
				++arr[c-1][r-1];
			++arr[c-1][r];
		}
		if (r-1>=0)
			++arr[c][r-1];
		if (r+1<w)
			++arr[c][r+1];
	}
	
	int output[q];
	for (int j=0; j<q; j++){
		int y, x;
		scanf("%d %d", &y, &x); // y = h , x = w
		
		output[j] = arr[x][y];
	}
	
	//show output
	for (int i=0; i<q; i++) {
		if (output[i] < 0) printf("Bomb\n");
		else printf("%d\n", output[i]);
	}
}