#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int matrix[100][100];
int number_edges=0;
int L[100];
int V=0;
int parent[100]={0};
int capacidade[100]={1};
int flow[100][100];


int BFS(int origem,int destino){

int i,j;
int x=0;
int z=0;

int discover[100]={0};
int maxcapacidade=0;
int nodobase;
nodobase = origem;
for(i=0;i<V;i++){
	parent[L[i]]=0;
	capacidade[L[i]]=0;
}


	while(z<V){
		
			for(j=0;j<V;j++){

				if(matrix[nodobase][L[j]]>0 && nodobase!=L[j]){	
					
					if(discover[L[j]]==0 && x==1 && L[j]!= parent[nodobase] && flow[nodobase][L[j]]<1){
						//discover[L[j]]=1;
						if(capacidade[nodobase] +1 >capacidade[L[j]]){
							parent[L[j]] = nodobase;
							capacidade[L[j]] = 1 + capacidade[nodobase];
						}
					}
					
				if(j<V && x==0){
					if(discover[L[j]]==0 && x==0){
						//discover[L[j]]=1; (capacidade[nodobase] +1) < (capacidade[L[j]] +1) &&
						if( capacidade[nodobase]!=capacidade[L[j]] && capacidade[L[j]] +1 >capacidade[nodobase] && nodobase!=origem && L[j]!=destino && flow[L[j]][nodobase]<1){
							
								parent[nodobase] = L[j];
								capacidade[nodobase] = 1 + capacidade[L[j]];
								
							}
						}
					}
				
			}

				if(j==V-1 && x==0){
						x=1;
						j=-1;
				}
				//comparar matrix[origem][L[j]];
		}
		
		//z++;
		x=0;
		discover[nodobase]=1;
		while(L[z]==nodobase || discover[L[z]]==1 ){
			z++;
		}
		nodobase = L[z];
		/*if(L[z]!=nodobase){
			nodobase = L[z];
		}else{
			z++;
			nodobase = L[z];
		}*/
	}
	return parent[destino];
}

int maxcap=0;
int seen[100]={0};
int original;
char pathstring[1024]="\n";

int DFS(int origem,int destino){
	int j,i;
	int x=0;
	int circula;
	//pathstring leva reset
	if(origem == destino){
		if(capacidade[destino]>maxcap){
			maxcap=capacidade[destino];
			//actualiza o melhor caminho
			circula = destino;
			while(circula != original){
				pathstring[x]=circula;
				circula = parent[circula];
				x++;
			}
				pathstring[x]=circula;
				pathstring[x+1]='-';

			//
			
			for(i=0;i<V;i++)
				seen[L[i]]=0;

			return 0;
		}else{

			for(i=0;i<V;i++)
				seen[L[i]]=0;
			return 0;
		}


	}

	for(j=0;j<V;j++){
		if(matrix[origem][L[j]]>0 && origem!=L[j] && L[j]!=original && L[j]!=parent[origem] && seen[L[j]]<1 && flow[origem][L[j]]<1){
			parent[L[j]] = origem;
			capacidade[L[j]] = capacidade[origem] + 1;
			seen[origem]=1;
			DFS(L[j],destino);
		}

	}
	return pathstring[0]; 



}


void  Ford_FulkersonDfs(int origem,int destino){
int circula=0;
int maxflow=0;
int navigate=0;
int i=0;

	while(DFS(origem,destino)){
		navigate=0;
		maxflow++;
		i=0;
		circula = destino;
		while(pathstring[navigate+1]!='-'){
			if(matrix[pathstring[navigate]][pathstring[navigate+1]] >0){
				if(flow[pathstring[navigate+1]][pathstring[navigate]]==0)
					flow[pathstring[navigate+1]][pathstring[navigate]]++;

				if(matrix[pathstring[navigate+1]][pathstring[navigate]] >0)
						flow[pathstring[navigate]][pathstring[navigate+1]] = -flow[pathstring[navigate+1]][pathstring[navigate]];
				}
			navigate++;
		}
		
		while(pathstring[i]!='\0'){
			pathstring[i]='\0';
			i++;
		}
		maxcap=0;
	}

}




void  Ford_Fulkerson(int origem,int destino){
int circula=0;
int maxflow=0;

	while(BFS(origem,destino)>0){
		maxflow++;
		circula = destino;
		while(circula!=origem){

			if(matrix[circula][parent[circula]] >0 && flow[parent[circula]][circula]<1 ){
					flow[parent[circula]][circula]++;

				if(matrix[parent[circula]][circula] >0)
						flow[circula][parent[circula]] = -flow[parent[circula]][circula];
			}
			circula = parent[circula];

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

		original =2;
		//DFS(2,6);
		Ford_FulkersonDfs(2,6);



	fclose(fp);
}