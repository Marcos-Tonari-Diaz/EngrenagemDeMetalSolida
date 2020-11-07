#include <stdio.h>
#include <memory>
#include <iostream>
#include "porta_controller.h"
#include "porta.h"
#include "player.h"

void Porta_controller::abre_fecha(Porta porta, Player jogador, int** Mapa_menor, int** Mapa_maior, Uint8* state, int n, int m) {
	int** P = new int*[m];
	for (int i = 0; i < n; ++i)
    		P[i] = new int[n];
    		
	for(int i = porta.get_x()*4; i < (porta.get_x()*4)+4; i++) {
		for(int j = porta.get_y()*4; j < (porta.get_y()*4)+4; j++) {
			P[j][i] = 1;
			if(i + 1 < n) P[j][i+1] = 1; if(i + 2 < n) P[j][j+2] = 1; if(i + 3 < n) P[j][j+3] = 1; if(i + 4 < n) P[j][j+4] = 1;
			if(j + 1 < m) P[j+1][i] = 1; if(j + 2 < m) P[j+2][j] = 1; if(j + 3 < m) P[j+3][j] = 1; if(j + 4 < m) P[j+4][j] = 1;
			if(i - 1 > 0) P[j][i-1] = 1; if(i - 2 > 0) P[j][j-2] = 1; if(i - 3 > 0) P[j][j-3] = 1; if(i - 4 > 0) P[j][j-4] = 1;
			if(j - 1 > 0) P[j-1][i] = 1; if(j - 2 > 0) P[j-2][j] = 1; if(j - 3 > 0) P[j-3][j] = 1; if(j - 4 > 0) P[j-4][j] = 1;
		}
	}
	
	if(P[jogador.get_pos().x][jogador.get_pos().y] != 1) return;
	
	else if (state[SDL_SCANCODE_E]) {
		if(porta.get_flag() == 0) {
			porta.set_flag(1);
			for(int i = porta.get_x()*4; i < (porta.get_x()*4)+4; i++) {
				for(int j = porta.get_y()*4; j < (porta.get_y()*4)+4; j++) {
					Mapa_menor[j][i] = 3; //codigo da porta aberta
				}
			}
			Mapa_maior[porta.get_y()][porta.get_x()] = 3;
			return;
		}
		else if(porta.get_flag() == 1) {
			porta.set_flag(0);
			for(int i = porta.get_x()*4; i < (porta.get_x()*4)+4; i++) {
				for(int j = porta.get_y()*4; j < (porta.get_y()*4)+4; j++) {
					Mapa_menor[j][i] = 2; //codigo da porta fechada
				}
			}
			Mapa_maior[porta.get_y()][porta.get_x()] = 2;
			return;
		}
	}
	else return;
}
