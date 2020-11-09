#include <stdio.h>
#include <memory>
#include <iostream>
#include "camera_controller.h"
#include "camera.h"
#include "player.h"

void Camera_controller::visao(Camera camera, int n, int m) {
	int aux;
	int y = camera.getY();
	int x = camera.getX();
	int direcao = camera.get_direcao();
	int alcance = camera.get_alcance();
	
	int** V = new int*[m];
	for (int i = 0; i < n; ++i)
    		V[i] = new int[n];
	
	switch (direcao) {
		case 0:	// cima
			x += tile_size/2;
			V[y][x] = 1;
			for (int i = y + 1; i < alcance + y + 1; i++) {
				if(i >= m) break;
				V[i][x] = 1;
				aux = x;
				while(1) {
					if(V[i-1][aux] == 1) {
						if(aux + 1 < n) V[i][aux+1] = 1;
						if(aux - 1 >= 0) V[i][aux-1] = 1;
					}
					if(V[i-1][aux+1] == 1) {
						if(aux + 1 < n) V[i][aux+1] = 1;
						if(aux + 2 < n) V[i][aux+2] = 1;
						if(aux - 1 >= 0) V[i][aux-1] = 1;
						if(aux - 2 >= 0) V[i][aux-2] = 1;
						aux++;
					}
					else break;
				}
			}
		camera.set_visao(V, n, m);
		return;

		case 1:	// baixo
			x += tile_size/2; y += tile_size;
			V[y][x] = 1;
			for (int i = y - 1; i > y - alcance - 1; i--) {
				if(i < 0) break;
				V[i][x] = 1;
				aux = x;
				while(1) {
					if(V[i+1][aux] == 1) {
						if(aux + 1 < n) V[i][aux+1] = 1;
						if(aux - 1 >= 0) V[i][aux-1] = 1;
					}
					if(V[i+1][aux+1] == 1) {
						if(aux + 1 < n) V[i][aux+1] = 1;
						if(aux + 2 < n) V[i][aux+2] = 1;
						if(aux - 1 >= 0) V[i][aux-1] = 1;
						if(aux - 2 >= 0) V[i][aux-2] = 1;
						aux++;
					}
					else break;
				}
			}
		camera.set_visao(V, n, m);
		return;

		case 2:	// direita
			x += tile_size; y += tile_size/2;
			V[y][x] = 1;
			for (int i = x + 1; i < alcance + x + 1; i++) {
				if(i >= n) break;
				V[y][i] = 1;
				aux = y;
				while(1) {
					if(V[aux][i-1] == 1) {
						if(aux + 1 < m) V[aux+1][i] = 1;
						if(aux - 1 >= 0) V[aux-1][i] = 1;
					}
					if(V[aux+1][i-1] == 1) {
						if(aux + 1 < m) V[aux+1][i] = 1;
						if(aux + 2 < m) V[aux+2][i] = 1;
						if(aux - 1 >= 0) V[aux-1][i] = 1;
						if(aux - 2 >= 0) V[aux-2][i] = 1;
						aux++;
					}
					else break;
				}
			}
		camera.set_visao(V, n, m);
		return;

		case 3:	// esquerda
			y += tile_size/2;
			V[y][x] = 1;
			for (int i = x - 1; i > x - alcance - 1; i--) {
				if(i < 0) break;
				V[y][i] = 1;
				aux = y;
				while(1) {
					if(V[aux][i+1] == 1) {
						if(aux + 1 < m) V[aux+1][i] = 1;
						if(aux - 1 >= 0) V[aux-1][i] = 1;
					}
					if(V[aux+1][i+1] == 1) {
						if(aux + 1 < m) V[aux+1][i] = 1;
						if(aux + 2 < m) V[aux+2][i] = 1;
						if(aux - 1 >= 0) V[aux-1][i] = 1;
						if(aux - 2 >= 0) V[aux-2][i] = 1;
						aux++;
					}
					else break;
				}
			}
		camera.set_visao(V, n, m);
		return;

		case 4:	// cima direita
			x += tile_size;
			for (int i = 0; i <= alcance; i++) {
				if((x + i) >= n || (y + i) >= m) break;
				V[y+i][x+i] = 1;
				for (int j = 1; j < (2*(alcance - i)) + 1; j++)  {
					if(y + j + i < m) V[y+j+i][x+i] = 1;
					if(x + j + i < n) V[y+i][x+j+i] = 1;
				}
			}
		camera.set_visao(V, n, m);
		return;

		case 5:	// baixo direita
			x += tile_size; y += tile_size;
			for (int i = 0; i <= alcance; i++) {
				if((x - i) < 0 || (y + i) >= m) break;
				V[y-i][x+i] = 1;
				for (int j = 1; j < (2*(alcance - i)) + 1; j++)  {
					if(y - j - i >= 0) V[y-j-i][x+i] = 1;
					if(x + j + i < m) V[y-i][x+j+i] = 1;
				}
			}
		camera.set_visao(V, n, m);
		return;

		case 6:	// cima esquerda
			for (int i = 0; i <= alcance; i++) {
				if((x + i) >= n || (y - i) < 0) break;
				V[y+i][x-i] = 1;
				for (int j = 1; j < (2*(alcance - i)) + 1; j++)  {
					if(y + j + i < n) V[y+j+i][x-i] = 1;
					if(x - j - i >= 0) V[y+i][x-j-i] = 1;
				}
			}
		camera.set_visao(V, n, m);
		return;

		case 7:	// baixo esquerda
			y += tile_size;
			for (int i = 0; i <= alcance; i++) {
				if((x - i) < 0 || (y - i) < 0) break;
				V[y-i][x-i] = 1;
				for (int j = 1; j < (2*(alcance - i)) + 1; j++)  {
					if(y - j - i >= 0) V[y-j-i][x-i] = 1;
					if(x - j - i >= 0) V[y-i][x-j-i] = 1;
				}
			}
		camera.set_visao(V, n, m);
		return;
	}
	return NULL;
}

void Camera_controller::deteccao(int** Mapa, Camera camera, Player jogador, int n, int m) {
	int x_visao = camera.getX();
	int y_visao = camera.getY();
	int x_jog = jogador.getX();
	int y_jog = jogador.getY();
	
	if((camera.get_visao())[x_jog][y_jog] != 1) {
		camera.set_detec(0);
		return;
	}

	int delta_x = x_jog - x_visao;	// arrumar a escala das coordenadas da camera
	int delta_y = y_jog - y_visao;
	int delta = delta_y/delta_x;

	if(delta_x > 0 && delta_y > 0) {
		for (int i = x_visao; i < x_visao + delta_x; i++) {
			for (int j = y_visao; j < y_visao + delta_y; j++) {
				if((y_visao - j) - (delta*(x_visao - i)) <= 3) {
					if(i < n && j < m) {
						if(Mapa[j][i] != 0) {
							camera.set_detec(0);
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
						if(Mapa[j][i] != 0) {
							camera.set_detec(0);
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
						if(Mapa[j][i] != 0) {
							camera.set_detec(0);
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
						if(Mapa[j][i] != 0) {
							camera.set_detec(0);
							return;
						}
					}
				}
			}
		}
	}
	camera.set_detec(1);
	return;
}
