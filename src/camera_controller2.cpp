#include "camera_controller2.h"

void Camera_controller2::visao(Map& mapa, Camera& camera, Player& jogador) {
	int direcao = camera.get_direcao();
	int cy = camera.getY();
	int cx = camera.getX();
	int px = jogador.getX() + tile_size/2;
	int py = jogador.getY() + tile_size/2;
	int limit = 1;
	switch (direcao) {
		case 0:	// cima
			if (
				(px + boundBoxSize/2> cx)
				&& (px + boundBoxSize/2 < cx+tile_size)
				&& (py + boundBoxSize/2 < cy )
				&& (py + boundBoxSize/2 > cy-tile_size)
			)
			camera.set_avistado(1);
			camera.set_detectado(1);
}
