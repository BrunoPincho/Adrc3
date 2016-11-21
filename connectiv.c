#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int matrix[100][100];
int number_edges=0;
int L[100];
int V=0;

void BFS(int origem){
int i,j,x;
int z=0;
int parent[100]={0};
int flow[100]={1};
int discover[100]={0};
int maxflow=0;
int nodobase;
nodobase = origem;


	while(z<V){
		

			for(j=0;j<V;j++){

				if(matrix[nodobase][L[j]]>0 && nodobase!=L[j]){	
					
					if(discover[L[j]]==0 ){
						//discover[L[j]]=1;
						if(flow[nodobase] +1 >flow[L[j]]){
							parent[L[j]] = nodobase;
							flow[L[j]] = 1 + flow[nodobase];
						}
					}

				}
				//comparar matrix[origem][L[j]];

			}
		
		z++;
		discover[nodobase]=1;
		if(L[z]!=nodobase){
			nodobase = L[z];
		}else{
			z++;
			nodobase = L[z];
		}
	}

}




int main(){
	int head;
	int tail;
	

	FILE* fp;
	fp = fopen("grafo.txt","r");

		while(fscanf(fp,"%d %d",&head,&tail)!=EOF){
				if(matrix[head][head]==0 ){
					matrix[head][head]=1;
					L[V] = head;
					V++;
				}

				matrix[head][tail]=1;
				number_edges++;				
		}

	
		BFS(1);



	fclose(fp);
}