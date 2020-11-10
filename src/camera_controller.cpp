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
	
	int** V = new int*[m];
	for (int i = 0; i < n; i++)
    		V[i] = new int[n];
	
	switch (direcao) {
		case 0:	// cima
			x += tile_size/2;
			camera.set_x_vis(x);
			if(y == y_jog && x == x_jog) {
				camera.set_avistado(1);
				goto aqui;
			}
			V[y][x] = 1;
			for (int i = y + 1; i < alcance + y + 1; i++) {
				if(i >= m) break;
				if(i == y_jog && x == x_jog) {
					camera.set_avistado(1);
					goto aqui;
				}
				V[i][x] = 1;
				aux = x;
				while(1) {
					if(V[i-1][aux] == 1) {
						if(aux + 1 < n) {
							if(i == y_jog && aux+1 == x_jog) {
								camera.set_avistado(1);
								goto aqui;
							}
							V[i][aux+1] = 1;
						}
						if(aux - 1 >= 0) {
							if(i == y_jog && aux-1 == x_jog) {
								camera.set_avistado(1);
								goto aqui;
							}
							V[i][aux-1] = 1;
						}
					}
					if(aux + 1 < n) {
						if(V[i-1][aux+1] == 1) {
							if(aux + 1 < n) {
								if(i == y_jog && aux+1 == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[i][aux+1] = 1;
							}
							if(aux + 2 < n) {
								if(i == y_jog && aux+2 == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[i][aux+2] = 1;
							}
							if(aux - 1 >= 0) {
								if(i == y_jog && aux-1 == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[i][aux-1] = 1;
							}
							if(aux - 2 >= 0) {
								if(i == y_jog && aux-2 == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[i][aux-2] = 1;
							}
							aux++;
						}
					}
					else break;
				}
			}
		camera.set_avistado(0);
		goto aqui;
		

		case 1:	// baixo
			x += tile_size/2; y += tile_size;
			camera.set_x_vis(x);
			camera.set_y_vis(y);
			if(y == y_jog && x == x_jog) {
				camera.set_avistado(1);
				goto aqui;
			}
			V[y][x] = 1;
			for (int i = y - 1; i > y - alcance - 1; i--) {
				if(i < 0) break;
				if(i == y_jog && x == x_jog) {
					camera.set_avistado(1);
					goto aqui;
				}
				V[i][x] = 1;
				aux = x;
				while(1) {
					if(V[i+1][aux] == 1) {
						if(aux + 1 < n) {
							if(i == y_jog && aux+1 == x_jog) {
								camera.set_avistado(1);
								goto aqui;
							}
							V[i][aux+1] = 1;
						}
						if(aux - 1 >= 0) {
							if(i == y_jog && aux-11 == x_jog) {
								camera.set_avistado(1);
								goto aqui;
							}
							V[i][aux-1] = 1;
						}
					}
					if(aux + 1 < n) {
						if(V[i+1][aux+1] == 1) {
							if(aux + 1 < n) {
								if(i == y_jog && aux+1 == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[i][aux+1] = 1;
							}
							if(aux + 2 < n) {
								if(i == y_jog && aux+2 == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[i][aux+2] = 1;
							}
							if(aux - 1 >= 0) {
								if(i == y_jog && aux-1 == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[i][aux-1] = 1;
							}
							if(aux - 2 >= 0) {
								if(i == y_jog && aux-2 == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[i][aux-2] = 1;
							}
							aux++;
						}
					}
					else break;
				}
			}
		camera.set_avistado(0);
		goto aqui;

		case 2:	// direita
			x += tile_size; y += tile_size/2;
			camera.set_x_vis(x);
			camera.set_y_vis(y);
			if(y == y_jog && x == x_jog) {
				camera.set_avistado(1);
				goto aqui;
			}
			V[y][x] = 1;
			for (int i = x + 1; i < alcance + x + 1; i++) {
				if(i >= n) break;
				if(y == y_jog && i == x_jog) {
					camera.set_avistado(1);
					goto aqui;
				}
				V[y][i] = 1;
				aux = y;
				while(1) {
					if(V[aux][i-1] == 1) {
						if(aux + 1 < m) {
							if(aux+1 == y_jog && i == x_jog) {
								camera.set_avistado(1);
								goto aqui;
							}
							V[aux+1][i] = 1;
						}
						if(aux - 1 >= 0) {
							if(aux-1 == y_jog && i == x_jog) {
								camera.set_avistado(1);
								goto aqui;
							}
							V[aux-1][i] = 1;
						}
					}
					if(aux + 1 < m) {
						if(V[aux+1][i-1] == 1) {
							if(aux + 1 < m) {
								if(aux+1 == y_jog && i == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[aux+1][i] = 1;
							}
							if(aux + 2 < m) {
								if(aux+2 == y_jog && i == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[aux+2][i] = 1;
							}
							if(aux - 1 >= 0) {
								if(aux-1 == y_jog && i == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[aux-1][i] = 1;
							}
							if(aux - 2 >= 0) {
								if(aux-2 == y_jog && i == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[aux-2][i] = 1;
							}
							aux++;
						}
					}
					else break;
				}
			}
		camera.set_avistado(0);
		goto aqui;

		case 3:	// esquerda
			y += tile_size/2;
			camera.set_y_vis(y);
			if(y == y_jog && x == x_jog) {
				camera.set_avistado(1);
				goto aqui;
			}
			V[y][x] = 1;
			for (int i = x - 1; i > x - alcance - 1; i--) {
				if(i < 0) break;
				if(y == y_jog && i == x_jog) {
					camera.set_avistado(1);
					goto aqui;
				}
				V[y][i] = 1;
				aux = y;
				while(1) {
					if(V[aux][i+1] == 1) {
						if(aux + 1 < m) {
							if(aux+1 == y_jog && i == x_jog) {
								camera.set_avistado(1);
								goto aqui;
							}
							V[aux+1][i] = 1;
						}
						if(aux - 1 >= 0) {
							if(aux-1 == y_jog && i == x_jog) {
								camera.set_avistado(1);
								goto aqui;
							}
							V[aux-1][i] = 1;
						}
					}
					if(aux + 1 < m) {
						if(V[aux+1][i+1] == 1) {
							if(aux + 1 < m) {
								if(aux+1 == y_jog && i == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[aux+1][i] = 1;
							}
							if(aux + 2 < m) {
								if(aux+2 == y_jog && i == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[aux+2][i] = 1;
							}
							if(aux - 1 >= 0) {
								if(aux-1 == y_jog && i == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[aux-1][i] = 1;
							}
							if(aux - 2 >= 0) {
								if(aux-2 == y_jog && i == x_jog) {
									camera.set_avistado(1);
									goto aqui;
								}
								V[aux-2][i] = 1;
							}
							aux++;
						}
					}
					else break;
				}
			}
		camera.set_avistado(0);
		goto aqui;

		case 4:	// cima direita
			x += tile_size;
			camera.set_x_vis(x);
			for (int i = 0; i <= alcance; i++) {
				if((x + i) >= n || (y + i) >= m) break;
				if(y+i == y_jog && x+i == x_jog) {
					camera.set_avistado(1);
					goto aqui;
				}
				V[y+i][x+i] = 1;
				for (int j = 1; j < (2*(alcance - i)) + 1; j++)  {
					if(y + j + i < m) {
						if(y+j+i == y_jog && x+i == x_jog) {
							camera.set_avistado(1);
							goto aqui;
						}
						V[y+j+i][x+i] = 1;
					}
					if(x + j + i < n) {
						if(y+i == y_jog && x+j+i == x_jog) {
							camera.set_avistado(1);
							goto aqui;
						}
						V[y+i][x+j+i] = 1;
					}
				}
			}
		camera.set_avistado(0);
		goto aqui;

		case 5:	// baixo direita
			x += tile_size; y += tile_size;
			camera.set_x_vis(x);
			camera.set_y_vis(y);
			for (int i = 0; i <= alcance; i++) {
				if((x - i) < 0 || (y + i) >= m) break;
				if(y-i == y_jog && x+i == x_jog) {
					camera.set_avistado(1);
					goto aqui;
				}
				V[y-i][x+i] = 1;
				for (int j = 1; j < (2*(alcance - i)) + 1; j++)  {
					if(y - j - i >= 0) {
						if(y-j-i == y_jog && x+i == x_jog) {
							camera.set_avistado(1);
							goto aqui;
							}
						V[y-j-i][x+i] = 1;
					}
					if(x + j + i < m) {
						if(y-i == y_jog && x+j+i == x_jog) {
							camera.set_avistado(1);
							goto aqui;
							}
						V[y-i][x+j+i] = 1;
					}
				}
			}
		camera.set_avistado(0);
		goto aqui;

		case 6:	// cima esquerda
			for (int i = 0; i <= alcance; i++) {
				if((x + i) >= n || (y - i) < 0) break;
				if(y+i == y_jog && x-i == x_jog) {
					camera.set_avistado(1);
					goto aqui;
				}
				V[y+i][x-i] = 1;
				for (int j = 1; j < (2*(alcance - i)) + 1; j++)  {
					if(y + j + i < n) {
						if(y+j+i == y_jog && x-i == x_jog) {
							camera.set_avistado(1);
							goto aqui;
						}
						V[y+j+i][x-i] = 1;
					}
					if(x - j - i >= 0) {
						if(y+i == y_jog && x-j-i == x_jog) {
							camera.set_avistado(1);
							goto aqui;
							}
						V[y+i][x-j-i] = 1;
					}
				}
			}
		camera.set_avistado(0);
		goto aqui;

		case 7:	// baixo esquerda
			y += tile_size;
			camera.set_y_vis(y);
			for (int i = 0; i <= alcance; i++) {
				if((x - i) < 0 || (y - i) < 0) break;
				if(y-i == y_jog && x-i == x_jog) {
					camera.set_avistado(1);
					goto aqui;
				}
				V[y-i][x-i] = 1;
				for (int j = 1; j < (2*(alcance - i)) + 1; j++)  {
					if(y - j - i >= 0) {
						if(y-j-i == y_jog && x-i == x_jog) {
							camera.set_avistado(1);
							goto aqui;
						}
						V[y-j-i][x-i] = 1;
					}
					if(x - j - i >= 0) {
						if(y-i == y_jog && x-j-i == x_jog) {
							camera.set_avistado(1);
							goto aqui;
						}
						V[y-i][x-j-i] = 1;
					}
				}
			}
		camera.set_avistado(0);
		goto aqui;
	}
	aqui:
	for (int i = 0; i < n; i++)
    		delete V[i];
    	delete V;
	return;
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
