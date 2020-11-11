#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H
#include "camera.h"
#include "player.h"
#include "map.h"
#include <stdio.h>
#include <memory>
#include <iostream>

class Camera_controller {
	private:
		int tile_size = 72;
		int boundBoxSize = 0;
	public:
		Camera_controller() = default;
		void visao(Map& mapa, Camera& camera, Player& jogador);
		void deteccao(Map& mapa, Camera& camera, Player& jogador);
		void setBoundBoxSize(int s);
		void setTileSize(int s);
};

#endif
