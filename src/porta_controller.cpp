#include "porta_controller.h"

void Porta_controller::abre_fecha(Porta& porta, Player& jogador, Map& mapa, const Uint8* state, int** collisionMap) {
	// nullptr used for resetting
	if (state == nullptr) return;
	if (state[SDL_SCANCODE_A]){
		if(//P[jogador.getY()+(boundBoxSize/2)][jogador.getX()+(boundBoxSize/2)] == 0
			// radial distance
			!((int) floor(sqrt((jogador.getX()+(boundBoxSize/2)-porta.getX()+(tile_size/2))
			*(jogador.getX()+(boundBoxSize/2)-porta.getX()+(tile_size/2)) 
			+(jogador.getY()+(boundBoxSize/2)-porta.getY()+(tile_size/2))
			*(jogador.getY()+(boundBoxSize/2)-porta.getY()+(tile_size/2))
			)) <= tile_size+tile_size/2)

		){
			return;
		}
		
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
