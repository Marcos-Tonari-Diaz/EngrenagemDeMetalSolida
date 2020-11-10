#ifndef PORTA_CONTROLLER_H
#define PORTA_CONTROLLER_H
#include "player.h"
#include "porta.h"
#include "map.h"

class Porta_controller {
	private:
		int tile_size = 20;
	public:
		void abre_fecha(Porta& porta, Player& jogador, Map& mapa, const Uint8* state);
};

#endif
