#include "camera_controller.h"

void Camera_controller::visao(Map& mapa, Camera& camera, Player& jogador) {
	int aux;
	int y = camera.getY();
	int x = camera.getX();
	int x_jog = jogador.getX() + tile_size/2;
	int y_jog = jogador.getY() + tile_size/2;
	int direcao = camera.get_direcao();
	int alcance = camera.get_alcance();
	int m = mapa.getHeight()*tile_size;
	int n = mapa.getWidth()*tile_size;

	switch (direcao) {
		case 0:	// cima
			x += tile_size/2;
			camera.set_x_vis(x);
			//V[y][x] = 1;
			if(y == y_jog && x == x_jog) { camera.set_avistado(1); return; }
			for(int i = 0; i < alcance; i++) {
				//V[y-i][x] = 1;
				if(y-i == y_jog && x == x_jog) { camera.set_avistado(1); return; }
				for(int j = 0; j < i + 1; j++) {
					//V[y-i][x+j] = 1;
					if(y-i == y_jog && x+j == x_jog) { camera.set_avistado(1); return; }
					//V[y-i][x-j] = 1;
					if(y-i == y_jog && x-j == x_jog) { camera.set_avistado(1); return; }
				}
			}
		camera.set_avistado(0);
		return;
		

		case 1:	// baixo
			x += tile_size/2; y += tile_size;
			camera.set_x_vis(x);
			camera.set_y_vis(y);
			//V[y][x] = 1;
			if(y == y_jog && x == x_jog) { camera.set_avistado(1); return; }
			for(int i = 0; i < alcance; i++) {
				//V[y+i][x] = 1;
				if(y+i == y_jog && x == x_jog) { camera.set_avistado(1); return; }
				for(int j = 0; j < i + 1; j++) {
					//V[y+i][x+j] = 1;
					if(y+i == y_jog && x+j == x_jog) { camera.set_avistado(1); return; }
					//V[y+i][x-j] = 1;
					if(y+i == y_jog && x-j == x_jog) { camera.set_avistado(1); return; }
				}
			}
		camera.set_avistado(0);
		return;

		case 2:	// direita
			x += tile_size; y += tile_size/2;
			camera.set_x_vis(x);
			camera.set_y_vis(y);
			//V[y][x] = 1;
			if(y == y_jog && x == x_jog) { camera.set_avistado(1); return; }
			for(int i = 0; i < alcance; i++) {
				//V[y][x+i] = 1;
				if(y == y_jog && x+i == x_jog) { camera.set_avistado(1); return; }
				for(int j = 0; j < i + 1; j++) {
					//V[y+j][x+i] = 1;
					if(y+j == y_jog && x+i == x_jog) { camera.set_avistado(1); return; }
					//V[y-j][x+j] = 1;
					if(y-j == y_jog && x+i == x_jog) { camera.set_avistado(1); return; }
				}
			}
		camera.set_avistado(0);
		return;

		case 3:	// esquerda
			y += tile_size/2;
			camera.set_y_vis(y);
			//V[y][x] = 1;
			if(y == y_jog && x == x_jog) { camera.set_avistado(1); return; }
			for(int i = 0; i < alcance; i++) {
				//V[y][x-i] = 1;
				if(y == y_jog && x-i == x_jog) { camera.set_avistado(1); return; }
				for(int j = 0; j < i + 1; j++) {
					//V[y+j][x-i] = 1;
					if(y+j == y_jog && x-i == x_jog) { camera.set_avistado(1); return; }
					//V[y-j][x-i] = 1;
					if(y-j == y_jog && x-i == x_jog) { camera.set_avistado(1); return; }
				}
			}
		camera.set_avistado(0);
		return;
	}
}

void Camera_controller::deteccao(Map& mapa, Camera& camera, Player& jogador) {
	int x_visao = camera.get_x_vis();
	int y_visao = camera.get_y_vis();
	int x_jog = jogador.getX() + tile_size/2;
	int y_jog = jogador.getY() + tile_size/2;
	int m = mapa.getHeight()*tile_size;
	int n = mapa.getWidth()*tile_size;

	if(camera.get_avistado() == 0) {
		camera.set_detectado(0);
		return;
	}

	int delta_x = x_jog - x_visao;
	int delta_y = y_jog - y_visao;
	int delta = delta_y/delta_x;

	if(delta_x > 0 && delta_y > 0) {
		for (int i = x_visao; i < x_visao + delta_x; i++) {
			for (int j = y_visao; j < y_visao + delta_y; j++) {
				if((y_visao - j) - (delta*(x_visao - i)) <= 3) {
					if(i < n && j < m) {
						if((mapa.get_textMap()[std::make_pair(i,j)] != "corridor") && (mapa.get_textMap()[std::make_pair(i,j)] != "porta_aberta")) {
							camera.set_detectado(0);
							return;
						}
					}
				}
			}
		}
	}

	else if(delta_x > 0 && delta_y < 0) {
		for (int i = x_visao; i < x_visao + delta_x; i++) {
			for (int j = y_visao; j > y_visao + delta_y; j--) {
				if((y_visao - j) - (delta*(x_visao - i)) <= 3) {
					if(i < n && j > 0) {
						if((mapa.get_textMap()[std::make_pair(i,j)] != "corridor") && (mapa.get_textMap()[std::make_pair(i,j)] != "porta_aberta")) {
							camera.set_detectado(0);
							return;
						}
					}
				}
			}
		}
	}

	else if(delta_x < 0 && delta_y > 0) {
		for (int i = x_visao; i > x_visao + delta_x; i--) {
			for (int j = y_visao; j < y_visao + delta_y; j++) {
				if((y_visao - j) - (delta*(x_visao - i)) <= 3) {
					if(i > 0 && j < m) {
						if((mapa.get_textMap()[std::make_pair(i,j)] != "corridor") && (mapa.get_textMap()[std::make_pair(i,j)] != "porta_aberta")) {
							camera.set_detectado(0);
							return;
						}
					}
				}
			}
		}
	}

	else if(delta_x < 0 && delta_y < 0) {
		for (int i = x_visao; i > x_visao + delta_x; i--) {
			for (int j = y_visao; j > y_visao + delta_y; j--) {
				if((y_visao - j) - (delta*(x_visao - i)) <= 3) {
					if(i > 0 && j > 0) {
						if((mapa.get_textMap()[std::make_pair(i,j)] != "corridor") && (mapa.get_textMap()[std::make_pair(i,j)] != "porta_aberta")) {
							camera.set_detectado(0);
							return;
						}
					}
				}
			}
		}
	}

	camera.set_detectado(1);
	return;
}