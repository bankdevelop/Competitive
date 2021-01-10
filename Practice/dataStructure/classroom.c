#include <stdio.h>
#include <stdlib.h>

int main(){
	char typeRoom;
	int height = 0, n = 0;
	int x, y;
	scanf("%c", &typeRoom);
	scanf("%d", &n);

	switch(typeRoom){
		case 's': height=5; break;
		case 'm': height=6; break;
		case 'l': height=8; break;
		default: height=0;
	}
	
		int room[height][5];
		for(int j=0; j<height; j++)
			for(int k=0; k<5; k++)
				room[j][k] = 0;
		
		for(int p=0; p<n; p++){
			scanf("%d %d", &x, &y);
			room[x-1][y-1]=1;
		}
				
		for(int j=0; j<height; j++){
			for(int k=0; k<5; k++){
				if(room[j][k]) printf("S ");
				else printf("X ");
			}
			printf("\n");
		}
}