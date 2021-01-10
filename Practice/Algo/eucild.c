#include <stdio.h>
#include <stdlib.h>

int gcd(int m, int n){
	if (n==0) return m;
    while( n != 0 ){
        int tmp = n;
        n = m % n;
        m = tmp;
	}
    return m;
}

int main(){
	int m, n;
	scanf("%d %d", &m, &n);
	
	if (m < n){
		int tmp = m;
		m = n;
		n = tmp;
	}
	
	printf("%d", gcd(m, n));
}