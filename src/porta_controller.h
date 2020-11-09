#ifndef PORTA_CONTROLLER_H
#define PORTA_CONTROLLER_H
#include "player.h"
#include "porta.h"

class Porta_controller {
	private:
		int tile_size = 20;
	public:
		void abre_fecha(Porta porta, Player jogador, int** Mapa_menor, int** Mapa_maior, Uint8* state, int n, int m);
};

#endif
