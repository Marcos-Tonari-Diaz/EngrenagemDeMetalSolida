#include "porta_controller.h"

void Porta_controller::abre_fecha(Porta& porta, Player& jogador, Map& mapa, const Uint8* state, int** collisionMap) {
	/*
	if(porta.get_flag() == 0) {
		mapa.get_textMap()[std::make_pair(porta.getX()/tile_size, porta.getY()/tile_size)] = "porta_fechada";
		collisionMap[porta.getY()/tile_size][porta.getX()/tile_size] = 0;
	}
	if(porta.get_flag() == 1) {
		mapa.get_textMap()[std::make_pair(porta.getX()/tile_size, porta.getY()/tile_size)] = "porta_aberta";
		collisionMap[porta.getY()/tile_size][porta.getX()/tile_size] = 1;
	}
	*/
	// nullptr used for resetting
	if (state == nullptr) return;
	if (state[SDL_SCANCODE_A]){
		int m = mapa.getHeight()*tile_size;
		int n = mapa.getWidth()*tile_size;
		
		// P[y][x]
		int** P = new int*[m];
		for (int i = 0; i < m; i++)
				P[i] = new int[n];
				
		for(int i = porta.getX(); i < porta.getX() + tile_size; i++) {
			for(int j = porta.getY(); j < porta.getY() + tile_size; j++) {
				P[j][i] = 0;
				for(int k = 1; k <= tile_size; k++) {
					if(i + k < n) P[j][i+k] = 1;
					if(j + k < m) P[j+k][i] = 1;	
					if(i - k >= 0) P[j][i-k] = 1;
					if(j - k >= 0) P[j-k][i] = 1;
				}
			}
		}

		std::cout << (int) floor(sqrt((jogador.getX()+(boundBoxSize/2)-porta.getX()+(tile_size/2))
			*(jogador.getX()+(boundBoxSize/2)-porta.getX()+(tile_size/2)) 
			+(jogador.getY()+(boundBoxSize/2)-porta.getY()+(tile_size/2))
			*(jogador.getY()+(boundBoxSize/2)-porta.getY()+(tile_size/2))
			)) << std::endl;
		if(//P[jogador.getY()+(boundBoxSize/2)][jogador.getX()+(boundBoxSize/2)] == 0
			// radial distance
			!((int) floor(sqrt((jogador.getX()+(boundBoxSize/2)-porta.getX()+(tile_size/2))
			*(jogador.getX()+(boundBoxSize/2)-porta.getX()+(tile_size/2)) 
			+(jogador.getY()+(boundBoxSize/2)-porta.getY()+(tile_size/2))
			*(jogador.getY()+(boundBoxSize/2)-porta.getY()+(tile_size/2))
			)) <= tile_size+tile_size/2)

		){
			//std::cout << "longe da porta!" << std::endl;
			for (int i = 0; i < m; i++)
				delete P[i];
			delete P;
			return;
		}
		
		for (int i = 0; i < m; i++)
			delete P[i];
		delete P;
		
		if(porta.get_flag() == 0) {
			porta.set_flag(1);
			mapa.get_textMap()[std::make_pair(porta.getX()/tile_size, porta.getY()/tile_size)] = "porta_aberta";
			collisionMap[porta.getY()/tile_size][porta.getX()/tile_size] = 1;
			//std::cout << "abre!" << std::endl;
			return;
		}
		else if(porta.get_flag() == 1) {
			porta.set_flag(0);
			mapa.get_textMap()[std::make_pair(porta.getX()/tile_size, porta.getY()/tile_size)] = "porta_fechada";
			collisionMap[porta.getY()/tile_size][porta.getX()/tile_size] = 0;
			//std::cout << "fecha!" << std::endl;
			return;
		}
		else return;
	}
}

void Porta_controller::setTileSize(int s){ tile_size = s;}
void Porta_controller::setBoundBoxSize(int s){ boundBoxSize = s;};
