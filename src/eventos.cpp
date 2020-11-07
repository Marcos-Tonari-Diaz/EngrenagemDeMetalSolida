#include <stdio.h>
#include <memory>
#include <iostream>
#include "eventos.h"
#include "player.h"
#include "porta.h"
#include "camera.h"

void Eventos::reset(Player jogador, std::vector<Porta> portas, std::vector<Camera> cameras, int x_inicial, int y_inicial) {
	int tam_cam = cameras.size();
	int tam_por = portas.size();
	for(int i = 0; i < tam_com; i++) {
		cameras[i].set_detec(0);
	}
	for(int i = 0; i < tam_por; i++) {
		portas[i].set_flag(0);
	}
	jogador.get_pos().x = x_inicial;
	jogador.get_pos().y = y_inicial;
}

char* Eventos::checagem(Player jogador, std::vector<Porta> portas, std::vector<Camera> cameras, int x_final, int y_final, int x_inicial, int y_inicial) {
	int delta_x; int delta_y;
	int tam_cam = cameras.size();
	for(int i = 0; i < tam_cam; i++) {
		if(cameras[i].get_detec() == 1) {
			reset(jogador, portas, cameras, x_inicial, y_inicial);
			return "detectado";
		}
	}
	delta_x = fabs(x_final - (jogador.get_pos().x));
	delta_y = fabs(y_final - (jogador.get_pos().y));
	if(delta_x <= 3 && delta_y <= 3) {
		reset(jogador, portas, cameras, x_inicial, y_inicial);
		return "fim de jogo";
	}
	return "nada acontece feijoada";
}
