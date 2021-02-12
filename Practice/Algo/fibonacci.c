#include <stdio.h>
#include <stdlib.h>

int main(){
	int n;
	scanf("%d", &n);
	
	if (n > 0) {
		if (n >= 1) printf("0\n");
		if (n >= 2) printf("1\n");
		if (n >= 3) {
			unsigned long long int a = 0, b = 1;
			while (n-- > 2) {
				unsigned long long int temp = a;
				a = b;
				b += temp;
				printf("%llu\n", b);
			}
		}
	}
}