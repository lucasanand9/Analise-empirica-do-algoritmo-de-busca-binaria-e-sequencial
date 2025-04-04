#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int tamanhos[] = {1000, 10000, 100000, 1000000, 2500000, 5000000, 7500000, 100000000, 150000000, 200000000, 300000000, 400000000, 600000000, 800000000, 1000000000};
int buscaSeq(int tam, int *v, int chave, int * contador);
int pesquisaBin(int tam, int *v, int chave, int * contador);
int pesquisaBinaria(int *v,int inicio, int fim, int chave, int * contador);


int main(){
	FILE * arq = fopen("dados.txt", "w");
	if(arq == NULL) return 0;
	clock_t clockInicial, clockFinal;
	int *v;
	int chave;
	int contador_bs;
	int contador_bb;
	float tempo, media;
	v = malloc(sizeof(int) * tamanhos[0]);
	fprintf(arq, "Tamanho,Tempo_bs,Tempo_bb,Interacao_bs,Interacao_bb\n");
	for (int i = 0; i < 15; i++){
		v = realloc(v, sizeof(int) * tamanhos[i]);
	
		for(int j = 0; j < tamanhos[i]; j++){
			v[j] = j;
		}
		chave = -1;
		media = 0;
		
		fprintf(arq, "%i,", tamanhos[i]);
		for(int j = 0; j < 10; j++){
			clockInicial = clock();
			buscaSeq(tamanhos[i], v, chave, &contador_bs);
			clockFinal = clock();
			tempo = (float)(clockFinal - clockInicial)/CLOCKS_PER_SEC; 
			// fprintf(arq, "Tempo: %fs\n", tempo);
			media += tempo;
		}
		fprintf (arq, "%f,", media/10);


		media = 0;
		for(int j = 0; j < 10; j++){
			clockInicial = clock();
			pesquisaBin(tamanhos[i], v, chave, &contador_bb);
			clockFinal = clock();
			tempo = (float)(clockFinal - clockInicial)/CLOCKS_PER_SEC; 
			// fprintf(arq,"Tempo: %fs\n", tempo);
			media += tempo;
		}
		fprintf(arq,"%f,", media/10);
		fprintf(arq,"%i,%i\n", contador_bs, contador_bb);
		
	}
	fclose(arq);
}

int buscaSeq(int tam, int *v, int chave, int * contador){
	(*contador) = 0;
	for(int i = 0; i < tam; i++){
		(*contador)++;
		if(v[i] == chave)
			return i;
	}
	return -1;
}

int pesquisaBin(int tam, int *v, int chave, int * contador){
	return pesquisaBinaria(v, 0, tam-1, chave, contador);
}

int pesquisaBinaria(int *v, int inicio, int fim, int chave, int * contador){
	int meio;
	(*contador)++;
	if(fim < inicio) return -1;
	meio = (inicio + fim)/2;
	if(chave == v[meio]) return meio;
	if(chave < v[meio]) return pesquisaBinaria(v, inicio, meio-1, chave, contador);
	return pesquisaBinaria(v, meio+1, fim, chave, contador);
}
