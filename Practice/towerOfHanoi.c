#include <stdio.h>
#include <stdlib.h>

int main(){
	int n;
	char a[20], b[20], c[20];
	scanf("%d", &n);
	scanf("%s %s %s", a, b, c);
	hanoi(n, a, b, c);
}

void hanoi(int n, char a[], char b[], char c[]){
	if (n==0) return;
	hanoi(n-1, a, c, b);
	printf("Move the disk %d from %s to %s\n", n, a, c);
	hanoi(n-1, b, a, c);
}