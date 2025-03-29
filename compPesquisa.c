#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// ate 450 milhoes vai tranquilo e 500 milhoes nao tanka
int tamanhos[] = {1000, 10000, 100000, 1000000, 5000000, 100000000, 200000000, 400000000};
int buscaSeq(int tam, int *v, int chave);
int pesquisaBin(int tam, int *v, int chave);
int pesquisaBinaria(int *v,int inicio, int fim, int chave);


int main(){
	FILE * arq = fopen("dados.txt", "a");
	if(arq == NULL) return 0;
	clock_t clockInicial, clockFinal;
	int *v;
	int chave;
	float tempo, media;
	v = malloc(sizeof(int) * tamanhos[0]);
	for (int i = 0; i < 8; i++){
		v = realloc(v, sizeof(int) * tamanhos[i]);
	
		srand(time(NULL));
		for(int j = 0; j < tamanhos[i]; j++){
			v[j] = j;
		}

		chave = v[rand()%(tamanhos[i]-1)];

		media = 0;
		fprintf(arq, "\nTamanho: %i - Funcao: Busca Sequencial\n", tamanhos[i]);
		for(int j = 0; j < 10; j++){
			clockInicial = clock();
			buscaSeq(tamanhos[i], v, chave);
			clockFinal = clock();
			tempo = (float)(clockFinal - clockInicial)/CLOCKS_PER_SEC; 
			fprintf(arq, "Tempo: %fs\n", tempo);
			media += tempo;
		}
		fprintf (arq, "\nMedia: %f\n", media/10);


		media = 0;
		fprintf(arq,"\nTamanho: %i - Funcao: Pesquisa Binaria\n", tamanhos[i]);
		for(int j = 0; j < 10; j++){
			clockInicial = clock();
			pesquisaBin(tamanhos[i], v, chave);
			clockFinal = clock();
			tempo = (float)(clockFinal - clockInicial)/CLOCKS_PER_SEC; 
			fprintf(arq,"Tempo: %fs\n", tempo);
			media += tempo;
		}
		fprintf(arq,"\nMedia: %f\n", media/10);
		
	}
	fclose(arq);
}

int buscaSeq(int tam, int *v, int chave){
	for(int i = 0; i < tam; i++){
		if(v[i] == chave)
			return i;
	}
	printf("O numero nao existe\n");
	return -1;
}

int pesquisaBin(int tam, int *v, int chave){
	return pesquisaBinaria(v, 0, tam-1, chave);
}

int pesquisaBinaria(int *v, int inicio, int fim, int chave){
	int meio;
	if(fim < inicio) return -1;
	meio = (inicio + fim)/2;
	if(chave == v[meio]) return meio;
	if(chave < v[meio]) return pesquisaBinaria(v, inicio, meio-1, chave);
	return pesquisaBinaria(v, meio+1, fim, chave);
}
