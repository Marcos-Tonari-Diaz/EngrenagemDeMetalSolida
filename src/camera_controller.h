#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H
#include "camera.h"
#include "player.h"
#include "map.h"
#include <stdio.h>
#include <memory>
#include <iostream>
#include "camera.h"
#include "player.h"

class Camera_controller {
	private:
		int tile_size = 20;
	public:
		void visao(Map& mapa, Camera& camera, Player& jogador);
		void deteccao(Map& mapa, Camera& camera, Player& jogador);
};

#endif
