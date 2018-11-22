// Função: Atividade parcial das disciplinas Linguagem de Programação e Algoritmos (UTFPR-PG)
// Autor: Cesar Mauricio Chauchuty, Gabriel da Cruz Rakovicz
// Data: 21/11/18
// Jogo: Pac-Man
// Versão: 1.5
// Compilador: TMD-GCC 4.9.2 64-bit Release

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

#define sleep(x) Sleep(1000 * (x))
#define nomeJogo() SetConsoleTitle("PacMan - Atividade Parcial")
#define tempoRandom() srand(time(NULL));
#define pt_br() setlocale (LC_ALL, "portuguese")
#define corJogo() system("color f")
#define limpaTela() printf("\033[H")
#define linha() printf("\n---------------------------------------------")

/*        Registros        */

struct Mapa{
	char vet_mapa[13][20], vet_pontos[13][20];
	int dificuldade;
}mapa;

struct Player{
	char tecla, simbolo;
	int pos_i, pos_j, nav, pontos, m_pontos, cheat;
}player;

struct Fantasma{
	char simbolo;
	int pos_i, pos_j, nav, ia, cont;
}fantasma[4];

/*        Procedimentos e Funções        */

// funcKbhit
void funcKbhit(){
	if(kbhit()){
			fflush(stdin);
			player.tecla = getch();
		}
}

// Colorir
void colorir(int F, int B) {
	WORD wColor = ((B & 0x0F) << 4) + (F & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

// Esconde o cursor
void esconderCursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

// Arte Pac
void artePac(){
	colorir(6,0);
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n");
	printf("    _ __   __ _  ___ _ __ ___   __ _ _ __     \n");
	printf("   | '_ \\ / _  |/ __| '_ ` _ \\ / _` | '_ \\    \n");
	printf("   | |_) | (_| | (__| | | | | | (_| | | | |   \n");
	printf("   | .__/ \\__._|\\___|_| |_| |_|\\__,_|_| |_|   \n");
	printf("   | |                                        \n");
	printf("   |_|                                        \n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n");
	colorir(15,0);

}

// Efeito de Loading
void loading(){
	int i;
	printf("\n\n\n\n\n\n\n\t\t   ");
	for(i = 0; i < 3 ; i++){
		printf(". ");
		Sleep(200);
	}
	system("cls");
}

// Opções Tela Inicial
int opcoesMenu(char tecla, int nav){
	char dificuldade[5];
	linha();
	switch(mapa.dificuldade){
		case 250:
			strcpy(dificuldade, "Fácil");
			break;
		case 150:
			strcpy(dificuldade, "Médio");
			break;
		case 120:
			strcpy(dificuldade, "Béééé");
			break;
	}
	switch(nav){
		case 0:
			colorir(3,0);
			printf("\n\t      >  Iniciar       ");
			colorir(15,0);
			printf("\n\t          Instruções   ");
			printf("\n\t          Dificuldade  ");
			printf("\n\t          Pontuação    ");
			printf("\n\t          Créditos     ");
			printf("\n\t          Sair         ");
			colorir(8,0);
			printf("\n\t\t\t\tNível: %s", dificuldade);
			colorir(15,0);
			if(tecla == 13){
				return 0;
			}
			break;
		case 1:

			printf("\n\t          Iniciar         ");
			colorir(3,0);
			printf("\n\t      >  Instruções       ");
			colorir(15,0);
			printf("\n\t          Dificuldade     ");
			printf("\n\t          Pontuação       ");
			printf("\n\t          Créditos        ");
			printf("\n\t          Sair            ");
			colorir(8,0);
			printf("\n\t\t\t\tNível: %s", dificuldade);
			colorir(15,0);
			if(tecla == 13){
				return 1;
			}
			break;
		case 2:
			printf("\n\t          Iniciar         ");
			printf("\n\t          Instruções      ");
			colorir(3,0);
			printf("\n\t      >  Dificuldade      ");
			colorir(15,0);
			printf("\n\t          Pontuação       ");
			printf("\n\t          Créditos        ");
			printf("\n\t          Sair            ");
			colorir(8,0);
			printf("\n\t\t\t\tNível: %s", dificuldade);
			colorir(15,0);
			if(tecla == 13){
				return 2;
			}
			break;
		case 3:
			printf("\n\t          Iniciar         ");
			printf("\n\t          Instruções      ");
			printf("\n\t          Dificuldade     ");
			colorir(3,0);
			printf("\n\t      >  Pontuação        ");
			colorir(15,0);
			printf("\n\t          Créditos        ");
			printf("\n\t          Sair            ");
			colorir(8,0);
			printf("\n\t\t\t\tNível: %s", dificuldade);
			colorir(15,0);
			if(tecla == 13){
				return 3;
			}
			break;
		case 4:

			printf("\n\t          Iniciar         ");
			printf("\n\t          Instrucões      ");
			printf("\n\t          Dificuldade     ");
			printf("\n\t          Pontuação       ");
			colorir(3,0);
			printf("\n\t      >  Créditos         ");
			colorir(15,0);
			printf("\n\t          Sair            ");
			colorir(8,0);
			printf("\n\t\t\t\tNível: %s", dificuldade);
			colorir(15,0);
			if(tecla == 13){
				return 4;
			}
			break;
		case 5:

			printf("\n\t          Iniciar         ");
			printf("\n\t          Instrucões      ");
			printf("\n\t          Dificuldade     ");
			printf("\n\t          Pontuação       ");
			printf("\n\t          Créditos        ");
			colorir(3,0);
			printf("\n\t      >  Sair             ");
			colorir(15,0);
			colorir(8,0);
			printf("\n\t\t\t\tNível: %s", dificuldade);
			colorir(15,0);
			if(tecla == 13){
				return 5;
			}
		}
		linha();
		printf("\n\t         Versão 1.5          ");
}

// Tela Instruções
void instrucoes(){
	system("cls");
	loading();
	artePac();
	printf("\t\t- INSTRUÇÕES -");
	linha();
	printf("\n Controle:\n");
	colorir(12,0);
	printf("\t   [W] Cima\t [A] Esquerda\n\t   [S] Baixo\t [D] Direita\n\n\t   [P] Pausar");
	colorir(15,0);
	linha();
	printf("\n Objetivo: \n");
	colorir(3,0);
	printf("\t   Coma todas as bolinhas no mapa.\n");
	printf("\n\t   Não deixe que os fantasmas o \n\t   toquem!");
	colorir(15,0);
	linha();
	colorir(8,0);
	printf("\n\n   Pressione qualquer tecla para voltar...");
	colorir(15,0);
	system("pause > nul");
	system("cls");
	loading();
}

// Tela Dificuldade
int dificuldade(){
		system("cls");
		loading();
		player.nav = 0;
		player.tecla = ' ';
	do{
		artePac();
		printf("\t\t- DIFICULDADE -");
		linha();
		funcKbhit();
		switch(player.tecla){
			case 'w':
				if(player.nav > 0){
					player.nav--;
					player.tecla = ' ';
				}
				break;
			case 's':
				if(player.nav < 2){
					player.nav++;
					player.tecla = ' ';
				}
		}
		switch(player.nav){
			case 0:
				colorir(3,0);
				printf("\n\t         >  Fácil     ");
				colorir(15,0);
				printf("\n\t             Médio    ");
				printf("\n\t             Béééé  ");
				funcKbhit();
				if(player.tecla == 13){
					mapa.dificuldade = 250;
					system("cls");
					loading();
					return 0;
				}
				break;
			case 1:
				printf("\n\t             Fácil    ");
				colorir(6,0);
				printf("\n\t         >  Médio     ");
				colorir(15,0);
				printf("\n\t             Béééé  ");
				funcKbhit();
				if(player.tecla == 13){
					mapa.dificuldade = 150;
					system("cls");
					loading();
					return 0;
				}
				break;
			case 2:
				printf("\n\t             Fácil    ");
				printf("\n\t             Médio    ");
				colorir(4,0);
				printf("\n\t         >  Béééé     ");
				colorir(15,0);
				funcKbhit();
				if(player.tecla == 13){
					mapa.dificuldade = 120;
					system("cls");
					loading();
					return 0;
				}
				break;
		}
		Sleep(200);
		limpaTela();
	}while(1);
	system("pause > nul");
	system("cls");
	loading();
}

// Tela Pontuação
void pontuacao(int pontos){
	system("cls");
	loading();
	artePac();
	printf("\t\t- PONTUAÇÃO -");
	linha();
	colorir(3,0);
	printf("\n\t    Pontuação Máxima: ");
	colorir(15,0);
	printf("%04d", player.m_pontos);
	colorir(8,0);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n   Pressione qualquer tecla para voltar...");
	colorir(15,0);
	system("pause > nul");
	system("cls");
	loading();
}

// Tela Créditos
void creditos(){
	system("cls");
	loading();
	artePac();
	printf("\t\t- CRÉDITOS -");
	linha();
	colorir(3,0);
	printf("\n\t   Cesar Mauricio Chauchuty");
	printf("\n\t   Gabriel Da Cruz Rakovicz");
	colorir(15,0);
	colorir(8,0);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n   Pressione qualquer tecla para voltar...");
	colorir(15,0);
	system("pause > nul");
	system("cls");
	loading();
}

// Tela Sair
void sair(){
	int i;
	system("cls");
	Sleep(500);
	printf("\n\n\n\t\t  Saindo");
	for(i = 0; i < 3; i++){
		printf(". ");
		Sleep(500);
	}
	// "Cheat"
	if(player.cheat == 1){
		colorir(4, 0);
		printf("\n\n");
		printf("\t  Béééééé!!!                           \n");
		printf("\n                    / /                 ");
		printf("\n                  _(.(.                 ");
		printf("\n                ,'9 )\\)`-.,.--.        ");
		printf("\n                `-.|           `.       ");
		printf("\n                   \\,      ,    \\)    ");
		printf("\n                    `.  )._\\   (\\     ");
		printf("\n                      |//   `-,//       ");
		printf("\n                      ]||    //""       ");
		printf("\n                      ""    ""          ");
		colorir(0, 0);
		sleep(2);
	}
	printf("\n\n");
	sleep(1);
	exit(0);
}

// Tela Você Perdeu
void vocePerdeu(){
	sleep(1);
	if(player.pontos > 0){
		player.pontos-= 10;
	}
	system("cls");
	loading();
	artePac();
	colorir(12,0);
	printf("\n\t\tVocê perdeu.");
	colorir(15,0);
	printf("\n\n\t\tPontos: ");
	colorir(3,0);
	printf("%04d", player.pontos);
	colorir(8,0);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n   Pressione qualquer tecla para voltar...");
	colorir(15,0);
	system("pause > nul");
	system("cls");
	loading();
	telaInicial();
}

// Tela Você Ganhou
void voceGanhou(){
	sleep(1);
	system("cls");
	loading();
	artePac();
	colorir(14,0);
	printf("\n\t\t Parabéns!\t\n \t\tVocê ganhou!");
	colorir(15,0);
	printf("\n\n\t\tPontos: ");
	colorir(3,0);
	printf("%04d", player.pontos-10);
	colorir(8,0);
	printf("\n\n\n\n\n\n\n\n\n\n\n   Pressione qualquer tecla para voltar...");
	colorir(15,0);
	system("pause > nul");
	system("cls");
	loading();
	telaInicial();
}

// Controlador
void controle(int pos_i, int pos_j, int tam_i, int tam_j){
	switch(player.tecla){
			case 'w':
			case 'W':
				if(mapa.vet_mapa[pos_i-1][pos_j] == '|'){
					break;
				}
				if(player.pos_i != 0){
					player.pos_i--;
				}

				break;
			case 's':
			case 'S':
				if(mapa.vet_mapa[pos_i+1][pos_j] == '|'){
					break;
				}
				if(player.pos_i != tam_i){
					player.pos_i++;
				}
				break;
			case 'a':
			case 'A':
				if(mapa.vet_mapa[pos_i][pos_j-1] == '|'){
					break;
				}
				if(player.pos_j != 0){
					player.pos_j--;
				}
				break;
			case 'd':
			case 'D':
				if(mapa.vet_mapa[pos_i][pos_j+1] == '|'){
					break;
				}
				if(player.pos_j != tam_j){
					player.pos_j++;
				}
				break;
			case 'p':
			case 'P':
				system("pause > nul");
				player.tecla = ' ';
		}
}

// Fantasmas Navegação
void fantasma_nav(int nav, int pos_i, int pos_j, int ia, int tam_i, int tam_j){
	switch(nav){
		case 0:
		case 1:
			switch(rand() % ia){
				case 0:
					if(mapa.vet_mapa[pos_i+1][pos_j] != '|' && pos_i != tam_i){
						fantasma[nav].pos_i++;
					}
					break;
				case 1:
					if(mapa.vet_mapa[pos_i-1][pos_j] != '|' && pos_i != 0){
						fantasma[nav].pos_i--;
					}
					break;
				case 2:
					if(mapa.vet_mapa[pos_i][pos_j+1] != '|' && pos_i != tam_j){
						fantasma[nav].pos_j++;
					}
					break;
				case 3:
					if(mapa.vet_mapa[pos_i][pos_j-1] != '|' && pos_i != 0){
						fantasma[nav].pos_j--;
					}
					break;
			}
			break;

		case 2:
		case 3:
			switch(rand() % ia){
			case 0:
			case 1:
			case 2:
				 if(player.pos_j < fantasma[nav].pos_j){
					if(mapa.vet_mapa[pos_i][pos_j-1] != '|'){
						fantasma[nav].pos_j--;
					} else {
						fantasma[nav].cont++;
						if(fantasma[nav].cont > 2){
							fantasma[nav].pos_i--;
							if(fantasma[nav].cont >= 8){
								fantasma[nav].cont = 0;
							}
						}
					}
				} else if(player.pos_j > fantasma[nav].pos_j){
					if(mapa.vet_mapa[pos_i][pos_j+1] != '|'){
						fantasma[nav].pos_j++;
					} else {
						fantasma[nav].cont++;
						if(fantasma[nav].cont > 2){
							fantasma[nav].pos_i++;
							if(fantasma[nav].cont >= 8){
								fantasma[nav].cont = 0;
							}
						}
					}
				} else if(player.pos_i < fantasma[nav].pos_i){
					if(mapa.vet_mapa[pos_i-1][pos_j] != '|'){
						fantasma[nav].pos_i--;
					} else {
						fantasma[nav].cont++;
						if(fantasma[nav].cont > 2){
							fantasma[nav].pos_i++;
							fantasma[nav].pos_j--;
							fantasma[nav].cont = 0;
						}
					}
				} else if(player.pos_i > fantasma[nav].pos_i){
					if(mapa.vet_mapa[pos_i+1][pos_j] != '|'){
						fantasma[nav].pos_i++;
					} else {
						fantasma[nav].cont++;
						if(fantasma[nav].cont > 2){
							fantasma[nav].pos_i++;
							fantasma[nav].pos_j--;
							fantasma[nav].cont = 0;
						}
					}
				}
		}
	}
}

// GamePlay
void gamePlay(){
	const int tam_i = 12, tam_j = 19;
	int i, j, bar = 0;

	player.simbolo = 67, player.pos_i = 1, player.pos_j = 2, player.pontos = 0;
	fantasma[0].simbolo = 35,fantasma[0].pos_i = 6, fantasma[0].pos_j = 9,  fantasma[0].nav = 0, fantasma[0].ia = 5;
	fantasma[1].simbolo = 36,fantasma[1].pos_i = 6, fantasma[1].pos_j = 10, fantasma[1].nav = 1, fantasma[1].ia = 5;
	fantasma[2].simbolo = 37,fantasma[2].pos_i = 7, fantasma[2].pos_j = 9,  fantasma[2].nav = 2, fantasma[2].ia = mapa.dificuldade / 21 /*%*/, fantasma[2].cont = 0;
	fantasma[3].simbolo = 38,fantasma[3].pos_i = 7, fantasma[3].pos_j = 10, fantasma[3].nav = 3, fantasma[3].ia = mapa.dificuldade / 17 /*%*/; fantasma[3].cont = 0;

	loading();

	// Limpar Mapa Pontos
	for(i = 0; i <= tam_i; i++){
		for(j = 0; j <= tam_j; j++){
				mapa.vet_pontos[i][j] = ' ';
		}
	}

	do{

		limpaTela();

		// Captura Tecla
		funcKbhit();

		// Controlador
		controle(player.pos_i, player.pos_j, tam_i, tam_j);

		// Fantasmas
		if(player.pontos > 1){
			fantasma_nav(fantasma[0].nav, fantasma[0].pos_i, fantasma[0].pos_j, fantasma[0].ia, tam_i, tam_j);
			fantasma_nav(fantasma[1].nav, fantasma[1].pos_i, fantasma[1].pos_j, fantasma[1].ia, tam_i, tam_j);
			fantasma_nav(fantasma[2].nav, fantasma[2].pos_i, fantasma[2].pos_j, fantasma[2].ia, tam_i, tam_j);
			fantasma_nav(fantasma[3].nav, fantasma[3].pos_i, fantasma[3].pos_j, fantasma[3].ia, tam_i, tam_j);
		}

		// Construção Mapa
		printf("\n");
		colorir(1,0);
		printf("    -------------------------------------\n");
		colorir(15,0);
		for(i = 0; i <= tam_i; i++){
			for(j = 0; j <= tam_j; j++){
				if(mapa.vet_pontos[i][j] == 'X'){
					mapa.vet_mapa[i][j] = ' ';
				} else {
					if(j == 0){
						mapa.vet_mapa[i][j] = '|';
					} else if(j == 3 && (i >= 4 && i <= 8)){
						mapa.vet_mapa[i][j] = '|';
					} else if(j == 6 && (i >= 3 && i <= 9)){
						mapa.vet_mapa[i][j] = '|';
					} else if(j == 8 && (i >= 6 && i <= 7)){
						mapa.vet_mapa[i][j] = '|';
					} else if(j == 11 && (i >= 6 && i <= 7)){
						mapa.vet_mapa[i][j] = '|';
					} else if(j == 13 && (i >= 3 && i <= 9)){
						mapa.vet_mapa[i][j] = '|';
					} else if(j == 16 && (i >= 4 && i <= 8)){
						mapa.vet_mapa[i][j] = '|';
					} else if(j == tam_j){
						mapa.vet_mapa[i][j] = '|';
					} else {
						mapa.vet_mapa[i][j] = 183;
					}
				}

				// Inserção do Player e Fantasmas
				mapa.vet_mapa[player.pos_i][player.pos_j] = player.simbolo;
				mapa.vet_mapa[fantasma[0].pos_i][fantasma[0].pos_j] = fantasma[0].simbolo;
				mapa.vet_mapa[fantasma[1].pos_i][fantasma[1].pos_j] = fantasma[1].simbolo;
				mapa.vet_mapa[fantasma[2].pos_i][fantasma[2].pos_j] = fantasma[2].simbolo;
				mapa.vet_mapa[fantasma[3].pos_i][fantasma[3].pos_j] = fantasma[3].simbolo;

			}
		}

		for(i = 0; i <= tam_i; i++){
			for(j = 0; j <= tam_j; j++){
				if(j == 0){
					printf("   ");
				}
				if(mapa.vet_mapa[i][j] == player.simbolo){
					colorir(14,0);
						printf("%c ", mapa.vet_mapa[i][j]);
					colorir(15,0);
				} else if (mapa.vet_mapa[i][j] == '#'){
					colorir(13,0);
						printf("%c ", mapa.vet_mapa[i][j]);
					colorir(15,0);
				} else if (mapa.vet_mapa[i][j] == '$'){
					colorir(12,0);
						printf("%c ", mapa.vet_mapa[i][j]);
					colorir(15,0);
				} else if (mapa.vet_mapa[i][j] == '%'){
					colorir(6,0);
						printf("%c ", mapa.vet_mapa[i][j]);
					colorir(15,0);
				} else if (mapa.vet_mapa[i][j] == '&'){
					colorir(11,0);
						printf("%c ", mapa.vet_mapa[i][j]);
					colorir(15,0);
				} else if(mapa.vet_mapa[i][j] == '|'){
					colorir(1,0);
					printf("%c ", mapa.vet_mapa[i][j]);
					colorir(15,0);
				} else {
					printf("%c ", mapa.vet_mapa[i][j]);
				}
			}
			printf("\n");
		}

		// Voce Perdeu
		if(player.pos_i == fantasma[0].pos_i && player.pos_j == fantasma[0].pos_j && player.cheat == 0){
				vocePerdeu();
		} else if(player.pos_i == fantasma[1].pos_i && player.pos_j == fantasma[1].pos_j && player.cheat == 0) {
				vocePerdeu();
		} else if(player.pos_i == fantasma[2].pos_i && player.pos_j == fantasma[2].pos_j && player.cheat == 0) {
				vocePerdeu();
		} else if(player.pos_i == fantasma[3].pos_i && player.pos_j == fantasma[3].pos_j && player.cheat == 0) {
				vocePerdeu();
		}

		// Marcação de Pontos
		if(mapa.vet_pontos[player.pos_i][player.pos_j] != 'X'){
			mapa.vet_pontos[player.pos_i][player.pos_j] = 'X';
				if(player.pontos > player.m_pontos){
					player.m_pontos = player.pontos;
				}
				player.pontos += 10;
				if(player.pontos % 200 == 0){
					bar++;
				}
				// Pontuação Máxima 2050
				if(player.pontos >= 2060){
					voceGanhou();
				}
		}

		colorir(1,0);
		printf("    -------------------------------------\n");
		colorir(15,0);

		colorir(8,0);
		printf("\t\t\t      Pontos: ");
		colorir(15,0);
		printf("%04d  ", player.pontos-10);
		colorir(15,0);

		// Alternar Pac-man
		if(player.simbolo == 67 && player.pontos > 1){
			player.simbolo = 79;
		} else {
			player.simbolo = 67;
		}

		// Dificuldade
		Sleep(mapa.dificuldade);

	}while(1);
}

// Tela Inicial
int telaInicial(){
	char   	pac = 67, vet_efeito[23];
	int 	i, pos_pac = 0, pontos = 0;
	player.tecla = ' ';
	player.nav = 0;
	player.cheat = 0;

	do{
		// Arte Pacman
		artePac();

		// Efeito Pacman
		for(i = 0; i <= 22; i++){
			if(pos_pac == i){
				if(pac == 67){
					pac = 79;
					vet_efeito[i] = pac;
				} else {
					pac = 67;
					vet_efeito[i] = pac;
				}
			} else{
				if(i >= pos_pac){
					vet_efeito[i] = 183;
				} else {
					vet_efeito[pos_pac-1] = 0;
				}
			}
		}
		for(i = 0; i <= 21; i++){
			printf(" %c", vet_efeito[i]);
		}
		pos_pac++;
		if(pos_pac > 22){
			pos_pac = 0;
		}

		/*        Menu       */

		// Controle
		if(kbhit()){
			fflush(stdin);
			player.tecla = getch();
			if((player.tecla == 'w' || player.tecla == 'W' || player.tecla == 72) && player.nav > 0){
				player.nav--;
			} else if((player.tecla == 's' || player.tecla == 'S' || player.tecla == 80) && player.nav < 5){
				player.nav++;
			}
			if(player.tecla == 'c'){
				player.cheat = 1;
			}
		}

		// Opções Menu
		switch(opcoesMenu(player.tecla, player.nav)){
			case 0:
				system("cls");
				gamePlay();
				player.tecla = ' ';
				break;
			case 1:
				instrucoes();
				player.tecla = ' ';
				break;
			case 2:
				dificuldade();
				player.tecla = ' ';
				break;
			case 3:
				pontuacao(pontos);
				player.tecla = ' ';
				break;
			case 4:
				creditos();
				player.tecla = ' ';
				break;
			case 5:
				sair();
				break;
		}

		Sleep(120);
		limpaTela();

	}while(1);

	return 0;
}

/*        Programa Principal        */

int main(){
	int i;
	mapa.dificuldade = 150;
	// Procedimentos Gerais
	nomeJogo();
	esconderCursor();
	tempoRandom();
	pt_br();
	corJogo();

	// Tela Inicial
	telaInicial();

	return 0;
}
