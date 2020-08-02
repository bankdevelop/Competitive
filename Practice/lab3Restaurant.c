#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char name[30], command[10];
	char name_arr[30][100];
	int n_input=0, n=0;
	while(1){
		scanf("%s", name);
		if(!strcmp(name,"end!")) break;
		strcpy(name_arr[n_input++], name);
	}
	
	int temp_num = -1, is_error=0;
	scanf("%s", command);
	if (!strcmp(command,"add")){
		
		scanf("%d", &n);
		for (int j=0; j<n; j++){
			scanf("%s", name);
			strcpy(name_arr[n_input++], name);
		}
		
	}else if (!strcmp(command,"delete")){
		
		scanf("%d", &n);
		if (n<=n_input){
			for (int j=0; j<n; j++){
				scanf("%s", name);
				for(int k=0; k<n_input; k++){
					if(!strcmp(name_arr[k], name)){
						strcpy(name_arr[k], "(deleted)");
					}
				}
			}
		}else{
			is_error=1;
		}
		
	}else if (!strcmp(command,"search")){
		scanf("%s", name);
		for (int p=0; p<n_input; p++){
			if (!strcmp(name_arr[p], name)){
				temp_num = p;
				break;
			}
		}
	}else is_error = 1;
	
	int index_n=1;
	if(!is_error){
		for(int m=0; m<n_input; m++){
			if(strcmp(name_arr[m], "(deleted)")){
				printf("%d %s\n", index_n, name_arr[m]);
				index_n++;
			}
		}
		if(!strcmp(command, "search")){
			if(temp_num == -1){
				printf("%s not found", name);
			}else{
				printf("%s is %d", name, temp_num+1);
			}
		}
		
	}else{
		printf("error!");
	}
}