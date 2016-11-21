#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int matrix[100][100];
int number_edges=0;


int main(){
	int head;
	int tail;

	FILE* fp;
	fp = fopen("grafo.txt","r");

		while(fscanf(fp,"%d %d",&tail,&head,)!=EOF){
				matrix[head][tail]=1;
				number_edges++;				
		}






	fclose(fp);
}