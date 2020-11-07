#ifndef EVENTOS_H
#define EVENTOS_H
#include "player.h"
#include "porta.h"
#include "camera.h"

class Eventos {
	public:
		char* checagem(Player jogador, std::vector<Porta> portas, std::vector<Camera> cameras, int x_final, int y_final, int x_inicial, int y_inicial);
		void reset(Player jogador, std::vector<Porta> portas, std::vector<Camera> cameras, int x_inicial, int y_inicial);
};

#endif
