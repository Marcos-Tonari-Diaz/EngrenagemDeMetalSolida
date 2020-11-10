#ifndef PORTA_CONTROLLER_H
#define PORTA_CONTROLLER_H
#include <iostream>
#include <memory>
#include "player.h"
#include "porta.h"
#include "map.h"

class Porta_controller {
	private:
		int tile_size = 0;
		int boundBoxSize = 0;
	public:
		Porta_controller() = default;
		void abre_fecha(Porta& porta, Player& jogador, Map& mapa, const Uint8* state);
		void setTileSize(int s);
		void setBoundBoxSize(int s);
};

#endif
