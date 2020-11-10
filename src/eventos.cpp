#include <stdio.h>
#include <memory>
#include <iostream>
#include <vector>
#include "eventos.h"
#include "player.h"
#include "porta.h"
#include "camera.h"

void Eventos::reset(Player& jogador, std::vector<Porta>& portas, std::vector<Camera>& cameras) {
	int tam_cam = cameras.size();
	int tam_por = portas.size();
	for(int i = 0; i < tam_cam; i++) {
		cameras[i].set_detectado(0);
	}
	for(int i = 0; i < tam_por; i++) {
		portas[i].set_flag(0);
	}
	jogador.setPosition(x_inicial, y_inicial);
}

int Eventos::checagem(Player& jogador, std::vector<Porta>& portas, std::vector<Camera>& cameras) {
	int delta_x; int delta_y;
	int tam_cam = cameras.size();
	for(int i = 0; i < tam_cam; i++) {
		if(cameras[i].get_detectado() == 1) {
			reset(jogador, portas, cameras);
			return 2;
		}
	}
	delta_x = fabs(x_final - (jogador.getX()));
	delta_y = fabs(y_final - (jogador.getY()));
	if(delta_x <= 3 && delta_y <= 3) {
		reset(jogador, portas, cameras);
		return 0;
	}
	return 1;
}
