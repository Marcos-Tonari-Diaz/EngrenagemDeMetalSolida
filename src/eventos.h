#ifndef EVENTOS_H
#define EVENTOS_H
#include "player.h"
#include "porta.h"
#include "camera.h"

class Eventos {
	private:
		int x_final = 300;
		int y_final = 300;
		int x_inicial = 0;
		int y_inicial = 0;
	public:
		int checagem(Player& jogador, std::vector<Porta>& portas, std::vector<Camera>& cameras);
		void reset(Player& jogador, std::vector<Porta>& portas, std::vector<Camera>& cameras);
};

#endif
