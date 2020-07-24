#include <stdio.h>
#include <stdlib.h>

int main(){
	char typeRoom;
	int isError = 0, height = 0, n = 0;
	int x, y;
	scanf("%c", &typeRoom);

	switch(typeRoom){
		case 's': height=5; break;
		case 'm': height=6; break;
		case 'l': height=8; break;
		default: isError=1;
	}
	
	if(!isError){
		scanf("%d", &n);
		if(n > 5*height || n<0) isError = 1;
	}
	
	if(!isError){
		int room[height][5];
		for(int j=0; j<height; j++)
			for(int k=0; k<5; k++)
				room[j][k] = 0;
		
		for(int p=0; p<n; p++){
			scanf("%d %d", &x, &y);
			--x;
			--y;
			while(room[y][x]){
				x++;
				if(x>5){
					x=1;
					y++;
				}
			}
			room[y][x]=1;
		}
				
		for(int j=0; j<height; j++){
			for(int k=0; k<5; k++){
				if(room[j][k]) printf("S");
				else printf("X");
				if(k<4){
					printf(" ");
				}
			}
			printf("\n");
		}
	}
}