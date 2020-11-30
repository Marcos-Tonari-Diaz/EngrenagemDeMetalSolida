#include <stdio.h>
#include <memory>
#include <iostream>
#include <vector>
#include "eventos.h"
#include "player.h"
#include "camera.h"

int Eventos::checagem(Player& jogador, Camera& camera, int tilesize, int boundingbox) {
	int delta_x; int delta_y;
	if(camera.get_detectado() == 1) 
		return 2;
	delta_x = fabs((x_final + tilesize/2) - (jogador.getX() + boundingbox/2));
	delta_y = fabs((y_final + tilesize/2) - (jogador.getY() + boundingbox/2));
	if(delta_x <= tilesize/4 && delta_y <= tilesize/4) {
		return 0;
	}
	return 1;
}

void Eventos::setEnd(int x, int y){
	x_final = x;
	y_final = y;
}
