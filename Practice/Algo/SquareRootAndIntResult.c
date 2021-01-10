#include <stdio.h>
#include <stdlib.h>

int squareInt(int m){
	int i = 1;
	while (i*i < m) i++;
	
	if (i*i == m) return i;
	return i-1;
}

int main(){
	int m;
	scanf("%d", &m);
	
	int result = squareInt(m);
	printf("%d", result);
}