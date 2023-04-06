#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>
#include"fogefoge2.h"
#include"mapa.h"
#include"ui.h"

MAPA m;
POSICAO heroi;
int tempilula = 0;

int paraondeofantasmavai(int xatual, int yatual, int* xdestino, int* ydestino){
	
	
	int opcoes[4][2] = {
	{xatual, yatual+1},
	{xatual+1, yatual},
	{xatual, yatual-1},
	{xatual-1, yatual}};
	
	srand(time(0));
	
	for(int i = 0; i < 10; i++){
		
		int posicao = rand() %  4;
		
		if(movimentovalidopelomapa(&m, opcoes[posicao][0], opcoes[posicao][1])){
			*xdestino = opcoes[posicao][0];
			*ydestino = opcoes[posicao][1];
			
			return 1;
		}
	}
	
	return 0;
}
		
void fantasmas(){
	MAPA copia;
	
	copiamapa(&copia, &m);
	
	for(int i = 0; i < m.linhas; i++){
		for(int j = 0; j < m.colunas; j++){
			if(copia.matriz[i][j] == FANTASMA){
				
				int xdestino, ydestino;
				
				int encontrou = paraondeofantasmavai(i, j, &xdestino, &ydestino);
				
				if(encontrou){
					andanomapa(&m, i, j, xdestino, ydestino);
				}
			}
		}
	}
	
	liberamapa(&copia);
}	
		
int acabou(){
	POSICAO pos;
	
	int fogefogenomapa = encontramapa(&m, &pos, HEROI);
	
	return !fogefogenomapa;
}

void move(char direcao){

int proximox = heroi.x, proximoy = heroi.y;
	
	
	switch(direcao){
		case ESQUERDA:
			proximoy--;
			break;
		case CIMA:
			proximox--;
			break;
		case BAIXO:
			proximox++;
			break;
		case DIREITA:
			proximoy++;
			break;
		default: 
		    system("cls");
	        fflush(stdin);
	        return;}
			
    if(!movimentovalidopelomapa(&m, proximox, proximoy)){
    	system("cls");
	    fflush(stdin);
		return;
	}
	
	if(ehpersonagem(&m, PILULA, proximox, proximoy)){
		tempilula = 1;
	}

	andanomapa(&m,heroi.x, heroi.y, proximox, proximoy);
	heroi.x = proximox;
	heroi.y = proximoy;	
	

	system("cls");
	fflush(stdin);
}


void explodepilula(){
	
	if(!tempilula){
		return;
	}
	
	explodepilula2(heroi.x, heroi.y, 0, 1, 3);
	explodepilula2(heroi.x, heroi.y, 0, -1, 3);
	explodepilula2(heroi.x, heroi.y, 1, 0, 3);
	explodepilula2(heroi.x, heroi.y, -1, 0, 3);
	
	tempilula = 0;
}

void explodepilula2(int x, int y,int somax, int somay,  int qtd){
	
	if(qtd == 0){
	return;}
	
	int novox = x + somax, novoy = y + somay;
	
	if(m.matriz[novox][novoy] == PAREDE_HORIZONTAL
	|| m.matriz[novox][novoy] == PAREDE_VERTICAL){return;}
			
	m.matriz[novox][novoy] = VAZIO;
	explodepilula2(novox, novoy, somax, somay, qtd - 1);
}

int main(){

	setlocale(LC_ALL, "Portuguese");
		
	//Matriz de 5 x 10.
	/*Temos 10 caracteres exatos aqui, na nossa matriz temos que declarar com 1 a mais, pois toda string termina 
	com "\0" no final, se lembra?*/
	
			printf("\n\t\t************************\n");
    		printf("\t\t******Bem-vindo ao******\n");
			printf("\t\t*******Foge-Foge********\n");
			printf("\t\t***Elmine os fantasmas**\n");
			printf("\t\t*Antes de ser eliminado*\n");
    		printf("\t\t************************\n\n");
    		system("pause");
			system("cls");
			
			printf("Utilize o 'w', 'a', 's', e 'd' para se movimentar pelo mapa.\nUtilize o 'b' para soltar a bomba, após pegar a pílula.\n\n");
			system("pause");
			system("cls");
			
			
	lemapa(&m);
	
	encontramapa(&m, &heroi, HEROI);
	

			do{
			
			
			printf("Tem pilula: %s\n", (tempilula ? "Sim" : "Não"));
	imprimemapa(&m);
	
	char comando;
	scanf(" %c", &comando);
	move(comando);
		if(comando == BOMBA){
			explodepilula();
		}
	fantasmas();
	
	
	} while(!acabou());
	
		
			liberamapa(&m);
}
