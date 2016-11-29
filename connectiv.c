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





int maxcap=0;
int seen[100]={0};
int original;
char pathstring[1024]="\n";
int unreachable[100]={0};
int nivel[100];

int DFS(int origem,int destino){
	int j,i;
	int x=0;
	int circula;
	int lvl=0;

	//pathstring leva reset
	if(origem == destino){
		if(capacidade[destino]>maxcap){

			maxcap=capacidade[destino];
			//actualiza o melhor caminho
			circula = destino;
			while(1){
				if(circula == original)
					break;

				pathstring[x]=circula;
				circula = parent[circula];
				x++;
			}
				pathstring[x]=circula;
				pathstring[x+1]='-';

			//
			seen[origem]=0;
			/*for(i=0;i<V;i++)
				seen[L[i]]=0;
				*/
			return 0;
		}else{
			seen[origem]=0;
		/*	for(i=0;i<V;i++)
				seen[L[i]]=0;
		*/
			return 0;
		}


	}

	//(capacidade[origem] + 1)>capacidade[L[j]] &&

	for(j=0;j<V;j++){
		if(matrix[origem][L[j]]>0 && origem!=L[j] && L[j]!=original && L[j]!=parent[origem] && seen[L[j]]<1 && (flow[origem][L[j]]<=0)){
			parent[L[j]] = origem;
			capacidade[L[j]] = capacidade[origem] + 1;
			seen[origem]=1;
			unreachable[L[j]]=0;
			DFS(L[j],destino);
		}
		if(matrix[origem][L[j]]>0 && origem!=L[j] && (flow[origem][L[j]]>0) && L[j]!=original && L[j]!=parent[origem] && seen[L[j]]<1){
			unreachable[L[j]]=1;
		}

	}
	seen[origem]=0;


	return pathstring[0];



}

void reset_flowscap(){
int i;

	for(i=0;i<V;i++){
		capacidade[L[i]]=1;
	}

}


void imprimeArestasBFS(int maxflow,int destino){
	int seen[100]={0};
	int distancia[100];


	int z,y,i;
	for(i=0;i<100;i++)
		distancia[i]=55555;

	distancia[original]=0;
	int nivel=0;
	int nodo;
	int unreach[100]={0};
	int sai_ciclo=0;

		while(sai_ciclo!=1){
			nodo=0;
			for(i=0;i<V;i++){

					if(distancia[L[i]]==nivel){
								nodo=L[i];
								seen[nodo]=1;
								z=0;
								while(z<V){
											if(matrix[nodo][L[z]]>0 && nodo!=L[z] && flow[nodo][L[z]]<1 && seen[L[z]]==0){
												distancia[L[z]]=nivel+1;
												seen[L[z]]=1;
													unreach[L[z]]=0;
											}
											if(matrix[nodo][L[z]]>0 && nodo!=L[z] && flow[nodo][L[z]]==1 && seen[L[z]]==0){
													//regista possiveis arestas de corte
													unreach[L[z]]=1;
											}
											z++;
									}


						}


				}
					if(nodo==0)
						sai_ciclo=1;

				nivel++;


			}

			//começar a tratar dos caminhos possiveis

			for(i=0;i<V;i++){
				if(unreach[L[i]]==1){
					for(z=0;z<V;z++){
						if(matrix[L[i]][L[z]]>0 && seen[L[z]]==1)
								printf("\n %d - %d\n",L[z],L[i]);
					}
				}

			}

}

void imprimeArestas(int maxflow,int destino){
int i,j;
int flowcount=0;
	printf("Um conjunto de arestas que disconectam o grafo sao por exemplo:\n");
	for(i=0;i<V;i++){
		if(unreachable[L[i]]>0){
			for(j=0;j<V;j++){



					if(matrix[L[i]][L[j]]>0 && L[i]!=L[j] && unreachable[L[j]]!=1 ) {
						printf("%d - %d\n",L[i],L[j]);
						flowcount++;

					}



					/*if(flowcount == maxflow )
						return;*/

			}
		}
		//flowcount=0; && flowcount>=matrix[L[i]][L[i]]

	}


}


void  Ford_FulkersonDfs(int origem,int destino){
int circula=0;
int maxflow=0;
int navigate=0;
int i=0;
int j;
original =origem;

	while(DFS(origem,destino)){
		navigate=0;
		maxflow++;
		i=0;
		circula = destino;
		while(pathstring[navigate+1]!='-'){

			if(matrix[pathstring[navigate]][pathstring[navigate+1]] >0){

				//if(flow[pathstring[navigate+1]][pathstring[navigate]]==0)
					flow[pathstring[navigate+1]][pathstring[navigate]]=1;

				//if(matrix[pathstring[navigate+1]][pathstring[navigate]] >0)
						flow[pathstring[navigate]][pathstring[navigate+1]] = -flow[pathstring[navigate+1]][pathstring[navigate]];
				}
			navigate++;
		}

		while(pathstring[i]!='\0'){
			pathstring[i]='\0';
			i++;
		}
		reset_flowscap();
		maxcap=0;
	}

	int countreachbles=0;
	for(i=0;i<V;i++){
		for(j=0;j<V;j++){
			if(matrix[L[i]][L[j]]>0 && unreachable[L[j]]==1 && L[i]!=L[j]){
				countreachbles++;
			}
		}
		if(countreachbles == matrix[L[i]][L[i]] && L[i]!=origem){
			unreachable[L[i]]=1;
		}else{
			countreachbles=0;
		}

	}


	imprimeArestasBFS(maxflow,destino);

	//imprimeArestas(maxflow,destino);

}








int main(){
	int head;
	int tail;
	int i;
	int j;


	FILE* fp;
	fp = fopen("grafo2.txt","r");

		while(fscanf(fp,"%d %d",&head,&tail)!=EOF){
				if(matrix[head][head]==0 ){
					//matrix[head][head]=1;
					L[V] = head;
					V++;
				}

				matrix[head][tail]=1;
				matrix[head][head]++;
				number_edges++;
		}

		/*
		for(i=0;i<V;i++){
			for(j=0;j<V;j++){
				if(L[i]!=L[j]){
					Ford_FulkersonDfs(L[i],L[j]);
				}
			}
		}*/

		Ford_FulkersonDfs(1,8);


	fclose(fp);
}
