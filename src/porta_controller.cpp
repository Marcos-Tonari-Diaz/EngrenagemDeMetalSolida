#include <stdio.h>
#include <memory>
#include <iostream>
#include "porta_controller.h"
#include "porta.h"
#include "player.h"

void Porta_controller::abre_fecha(Porta& porta, Player& jogador, int** Mapa_menor, int** Mapa_maior, Uint8* state, int n, int m) {
	int** P = new int*[m];
	for (int i = 0; i < n; ++i)
    		P[i] = new int[n];
    		
	for(int i = porta.getX(); i < porta.getX() + tile_size; i++) {
		for(int j = porta.getY(); j < porta.getY() + tile_size; j++) {
			P[j][i] = 1;
			if(i + 1 < n) P[j][i+1] = 1; if(i + 2 < n) P[j][j+2] = 1; if(i + 3 < n) P[j][j+3] = 1; if(i + 4 < n) P[j][j+4] = 1;
			if(j + 1 < m) P[j+1][i] = 1; if(j + 2 < m) P[j+2][j] = 1; if(j + 3 < m) P[j+3][j] = 1; if(j + 4 < m) P[j+4][j] = 1;
			if(i - 1 > 0) P[j][i-1] = 1; if(i - 2 > 0) P[j][j-2] = 1; if(i - 3 > 0) P[j][j-3] = 1; if(i - 4 > 0) P[j][j-4] = 1;
			if(j - 1 > 0) P[j-1][i] = 1; if(j - 2 > 0) P[j-2][j] = 1; if(j - 3 > 0) P[j-3][j] = 1; if(j - 4 > 0) P[j-4][j] = 1;
		}
	}
	
	if(P[jogador.getX()][jogador.getY()] != 1) return;
	
	for (int i = 0; i < n; ++i)
		delete P[i];
	delete P;
	
	else if (state[SDL_SCANCODE_E]) {
		if(porta.get_flag() == 0) {
			porta.set_flag(1);
			Mapa_maior[porta.getY()/tile_size][porta.getX()/tile_size] = 3;
			return;
		}
		else if(porta.get_flag() == 1) {
			porta.set_flag(0);
			Mapa_maior[porta.getY()/tile_size][porta.getX()/tile_size] = 2;
			return;
		}
	}
	else return;
}
