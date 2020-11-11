#ifndef EVENTOS_H
#define EVENTOS_H
#include <stdio.h>
#include <memory>
#include <iostream>
#include <vector>
#include "player.h"
#include "porta.h"
#include "porta_controller.h"
#include "camera.h"
#include <math.h>

class Eventos {
	private:
		int x_final = 72*9;
		int y_final = 72*9;
		int x_inicial = 0;
		int y_inicial = 0;
	public:
		int checagem(Player& jogador, Camera& cameras, int tilesize, int boundingbox);
		void setEnd(int x, int y);
		//void reset(Player& jogador, std::vector<std::shared_ptr<Porta>>& portas, std::vector<std::shared_ptr<Camera>>& cameras, Map& mapa, int** collisionMap, Porta_controller& portacontroller);
};

#endif
