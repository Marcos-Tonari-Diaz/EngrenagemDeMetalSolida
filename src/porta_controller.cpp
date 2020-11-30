#include "porta_controller.h"

void Porta_controller::abre_fecha(Porta& porta, Player& jogador, Map& mapa, const Uint8* state, int** collisionMap) {
	int m = mapa.getHeight()*tile_size;
	int n = mapa.getWidth()*tile_size;
	int prox = 0;

	for(int i = porta.getX(); i < porta.getX() + tile_size; i++) {
		for(int j = porta.getY(); j < porta.getY() + tile_size; j++) {
			//P[j][i] = 1;
			if((i == jogador.getX() && j == jogador.getY()) || (i == jogador.getX() && j == jogador.getY() + boundBoxSize - 2) ||
			(i == jogador.getX() + boundBoxSize - 2 && j == jogador.getY()) || (i == jogador.getX() + boundBoxSize - 2 && j == jogador.getY() + boundBoxSize - 2)) {
				return;	// Isso impede que a porta seja fechada dentro dela mesma
			}
			for(int k = 1; k <= tile_size; k++) {
				//P[j][i+k] = 1;
				if((i+k == jogador.getX() && j == jogador.getY()) || (i+k == jogador.getX() && j == jogador.getY() + boundBoxSize) ||
				(i+k == jogador.getX() + boundBoxSize && j == jogador.getY()) || (i+k == jogador.getX() + boundBoxSize && j == jogador.getY() + boundBoxSize)) {
					prox = 1;
				}
				//P[j+k][i] = 1;
				if((i == jogador.getX() && j+k == jogador.getY()) || (i == jogador.getX() && j+k == jogador.getY() + boundBoxSize) ||
				(i == jogador.getX() + boundBoxSize && j+k == jogador.getY()) || (i == jogador.getX() + boundBoxSize && j+k == jogador.getY() + boundBoxSize)) {
					prox = 1;
				}	
				//P[j][i-k] = 1;
				if((i-k == jogador.getX() && j == jogador.getY()) || (i-k == jogador.getX() && j == jogador.getY() + boundBoxSize) ||
				(i-k == jogador.getX() + boundBoxSize && j == jogador.getY()) || (i-k == jogador.getX() + boundBoxSize && j == jogador.getY() + boundBoxSize)) {
					prox = 1;
				}
				//P[j-k][i] = 1;
				if((i == jogador.getX() && j-k == jogador.getY()) || (i == jogador.getX() && j-k == jogador.getY() + boundBoxSize) ||
				(i == jogador.getX() + boundBoxSize && j-k == jogador.getY()) || (i == jogador.getX() + boundBoxSize && j-k == jogador.getY() + boundBoxSize)) {
					prox = 1;
				}
			}
		}
	}

	if (state[SDL_SCANCODE_E] && prox) {
		if(porta.get_flag() == 0) {
			porta.set_flag(1);
			mapa.get_textMap()[std::make_pair(porta.getX()/tile_size, porta.getY()/tile_size)] = "porta_aberta";
			collisionMap[porta.getY()/tile_size][porta.getX()/tile_size] = 1;
			return;
		}
		else if(porta.get_flag() == 1) {
			porta.set_flag(0);
			mapa.get_textMap()[std::make_pair(porta.getX()/tile_size, porta.getY()/tile_size)] = "porta_fechada";
			collisionMap[porta.getY()/tile_size][porta.getX()/tile_size] = 0;
			return;
		}
	}
	else return;
}

void Porta_controller::setTileSize(int s){ tile_size = s;}
void Porta_controller::setBoundBoxSize(int s){ boundBoxSize = s;};
