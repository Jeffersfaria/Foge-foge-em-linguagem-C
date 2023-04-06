#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mapa.h"

void copiamapa(MAPA* destino, MAPA* origem){
	destino->linhas = origem->linhas;
	destino->colunas = origem->colunas;
	
	alocamapa(destino);
		for(int i = 0; i < origem->linhas; i++){
			strcpy(destino->matriz[i], origem->matriz[i]);
		}
}

void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino){
		
		char personagem = m->matriz[xorigem][yorigem];
		m->matriz[xdestino][ydestino] = personagem;
		m->matriz[xorigem][yorigem] = VAZIO;
}

int encontramapa(MAPA* m, POSICAO* p, char c){

	
	//Acha a pocisão do foge-foge
	for(int i = 0; i < m->linhas; i++){
		for(int j = 0; j < m->colunas; j++){
			if(m->matriz[i][j] == c){
				p->x = i;
				p->y = j;
				return 1;
			}
		}
	}
	return 0;
}

int ehpersonagem(MAPA* m, char personagem, int x, int y) {
	return
		m->matriz[x][y] == personagem;
}

void liberamapa(MAPA* m){
	for(int i = 0; i < m->linhas; i ++){
			free(m->matriz[i]);
	}
			free(m->matriz);
}

void alocamapa(MAPA* m){

//Não esquecer o detalhe do "+1", por causa do "/0". 
m->matriz = malloc(sizeof(char*) * m->linhas);
		for(int i = 0; i < m->linhas; i++){
		(m->matriz[i] = malloc(sizeof(char) * m->colunas + 1));
		}
}

void lemapa(MAPA* m){

	FILE* f;
	f = fopen("mapa.txt", "r");
	if(f==0){
		printf("Erro na leitura do mapa\n");
		exit(1);
	}	
	
	fscanf(f, "%d %d", &(m->linhas), &(m->colunas));
	//printf("Linhas: %d \nColunas: %d \n", linhas, colunas);
	
	
	//Alocação dinâmica de memória(matriz nesse caso)
	
/*Ponteiro de ponteiro "**", pois uma matriz é um ponteiro de ponteiro, tendo em vista que um array é um ponteiro
e uma matriz aponta para arrays(linhas)
	int** v = malloc(sizeof(int*) * 5);
		for(int i = 0; i < 5; i++){
			v[i] = malloc(sizeof(int) * 10);
		}

v[0][0] = 10;
v[1][2] = 12;

printf("Inteiro alocado %d %d\n", v[0][0], v[1][2]);

//Para limpar a matriz toda
	for(int i = 0; i < 5; i ++){
		free(v[i]);
	}
	free(v);
*/

	alocamapa(m);
	
//Ele lê a linha toda, ex: mapa[0] ele lê a linha 0 toda, da matriz, passa pra mapa[1], lê, e assim por diante... 
		for(int i = 0; i< 5; i++){
			fscanf(f, "%s", m->matriz[i]);
		
		}	
		
		fclose;
}
/*
Está em outro arquivo agora "iu.c"
void imprimemapa(MAPA* m){
		
		for(int i = 0; i< m->linhas; i++){
			printf("%s\n", m->matriz[i]);
		
		}
}*/

int movimentovalidopelomapa(MAPA* m, int x, int y){

	if(x >= m->linhas || y >= m->colunas || m->matriz[x][y] == PAREDE_HORIZONTAL || m->matriz[x][y] == PAREDE_VERTICAL ||  m->matriz[x][y] == FANTASMA){
		
		    return 0;}
	else if(m->matriz[x][y] == HEROI|| m->matriz[x][y] == VAZIO){
	        return 1;
			}
	
	}

/*Daria pra apenas usar este "if" no fogefoge2.c,no lugar da função acima, o código ficaria menor, porém, separando
em uma função, com um nome claro e conciso, ajuda outros programadores a entenderem o código, sem precisar ficar
interpretando comandos, poupando tempo.

  if(proximox >= m.linhas || proximoy >= m.colunas || m.matriz[proximox][proximoy] != '.'){
			system("cls");
	        fflush(stdin);
	        return;*/
		
