#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

#define limpaTela() printf("\033[H");

// Esconde o cursor
void esconderCursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

struct Mapa{
	char vet[10][10];
}mapa;

struct Pac{
	char simbolo;
	int posicao[2]; // posicao[0] = Linha, posicao[1] = Coluna
	char tecla;
}pac;

// GamaPlay
void gamePlay(){
		int i, j;
	// Inicialização Pac
	pac.simbolo = 67;
	pac.posicao[0] = 5;
	pac.posicao[1] = 5;
	// Fim Inicialização
	system("");
	
	do{	
		printf("Movimento PacMan\n\n");
		printf("Controlador: W A S D\n\n");
		
		// Controlador
		// Kbhit irá executar o laço condicional quando alguma tecla for apertada.
		if(kbhit()){
			fflush(stdin);
			pac.tecla = getch();
		}
		
		// Mudando posição do Pac
		switch(pac.tecla){
			case 'w':
				// Limita que suba quando estiver na linha 0
				if(pac.posicao[0] != 0){
					pac.posicao[0] -= 1;
				}
				break;
			case 's':
				// Limita que desça quando estiver na linha 0
				if(pac.posicao[0] != 9){
					pac.posicao[0] += 1;
				}
				break;
			case 'a':
				// Limita que o movimento à esquerda quando estiver na coluna 0
				if(pac.posicao[1] != 0){
					pac.posicao[1] -= 1;
				}
				break;
			case 'd':
				// Limita que o movimento à direita quando estiver na coluna 10
				if(pac.posicao[1] != 9){
					pac.posicao[1] += 1;
				}
		
		}
		
		// Fim Controlador
		
		// Construir Mapa
		for(i = 0; i < 10; i++){
			for(j = 0; j < 10; j++){
				mapa.vet[i][j] = 250;
			}
		}
		mapa.vet[pac.posicao[0]][pac.posicao[1]] = pac.simbolo;
		// Fim Construir Mapa
		
		// Imprimir Tecla (Kbhit + Getch)
		
		printf("Tecla: %c\n", pac.tecla);
		printf("\nPosicao Linha: %d Posicao Coluna: %d\n\n", pac.posicao[0],pac.posicao[1]);
		
		// Imprimir Mapa
		for(i = 0; i < 10; i++){
			for(j = 0; j < 10; j++){
				printf("%c ", mapa.vet[i][j]);
			}
			printf("\n");
		}
		// Fim Imprimir Mapa
		
		// Atualização em 2ms
		usleep(200000);
		limpaTela();
	}while(1);
}

int main(){
	esconderCursor();
	gamePlay();
	return 0;
}
