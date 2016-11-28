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
		if(matrix[origem][L[j]]>0 && origem!=L[j] && L[j]!=original && L[j]!=parent[origem] && seen[L[j]]<1 && (flow[origem][L[j]]<1)){
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
	int i,j;
	int flowcount=0;
	int lvl=0;
	int visto;
	int descoberto[100]={0};
	int circula=0;
	circula = original;
	int parente[100]={0};
	int nivel[100]={5555555};
	nivel[original]=0;
	int next=101;
	int n_v=0;



	while(visto<30){

		for(i=0;i<V;i++){
			if(matrix[circula][L[i]]==1 && circula!=L[i] && descoberto[L[i]]==0 && flow[circula][L[i]]<1){
				parente[L[i]]=circula;
				nivel[L[i]]=nivel[circula]+1;
				descoberto[L[i]]=1;
			}

			if(matrix[circula][L[i]]==1 && circula!=L[i] && descoberto[L[i]]==0 && flow[circula][L[i]]==1){
				printf("\n%d - %d\n",circula,L[i]);
				//regista aresta
			}

		}
		lvl++;
		j=0;
				while(circula!=next){

					if(nivel[L[j]]==lvl){
						next=L[j];
						circula = next;
					}
					j++;
				}
				visto++;

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


	//imprimeArestasBFS(maxflow,destino);

	//imprimeArestas(maxflow,destino);

}








int main(){
	int head;
	int tail;
	int i;
	int j;


	FILE* fp;
	fp = fopen("grafo.txt","r");

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

		Ford_FulkersonDfs(2,6);


	fclose(fp);
}
