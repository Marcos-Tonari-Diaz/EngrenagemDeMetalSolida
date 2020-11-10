#include <stdio.h>
#include <memory>
#include <iostream>
#include "porta_controller.h"
#include "porta.h"
#include "player.h"
#include "map.h"

void Porta_controller::abre_fecha(Porta& porta, Player& jogador, Map& mapa, Uint8* state) {
	int m = mapa.getHeight()*tile_size;
	int n = mapa.getWidth()*tile_size;
	
	int** P = new int*[m];
	for (int i = 0; i < n; i++)
    		P[i] = new int[n];
    		
	for(int i = porta.getX(); i < porta.getX() + tile_size; i++) {
		for(int j = porta.getY(); j < porta.getY() + tile_size; j++) {
			P[j][i] = 1;
			for(int k = 1; k < tile_size; k++) {
				if(i + k < n) P[j][i+k] = 1;
				if(j + k < m) P[j+k][i] = 1;	
				if(i - k >= 0) P[j][i-k] = 1;
				if(j - k >= 0) P[j-1][i] = 1;
			}
		}
	}
	
	if(P[jogador.getX()][jogador.getY()] != 1) return;
	
	for (int i = 0; i < n; i++)
		delete P[i];
	delete P;
	
	if (state[SDL_SCANCODE_E]) {
		if(porta.get_flag() == 0) {
			porta.set_flag(1);
			mapa.get_textMap()[std::make_pair(porta.getX()/tile_size, porta.getY()/tile_size)] = "porta_aberta";
			return;
		}
		else if(porta.get_flag() == 1) {
			porta.set_flag(0);
			mapa.get_textMap()[std::make_pair(porta.getX()/tile_size, porta.getY()/tile_size)] = "porta_fechada";
			return;
		}
	}
	else return;
}
