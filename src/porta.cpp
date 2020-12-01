#include "porta.h"
#include "element.h"

Porta::Porta(int x, int y, int flag) {
	this->setPosition(x, y);
	this->flag = flag;
}

int Porta::get_flag() {
	return (this->flag);
}

void Porta::set_flag(int flag) {
	this->flag = flag;
}

void Porta::atualiza_porta(int** collisionMap, int tile_size, Map& mapa) {
	if(this->flag == 1) {
		collisionMap[this->getY()/tile_size][this->getX()/tile_size] = 1;
		mapa.get_textMap()[std::make_pair(this->getX()/tile_size, this->getY()/tile_size)] = "porta_aberta";
	}
	else if(this->flag == 0) {
		collisionMap[this->getY()/tile_size][this->getX()/tile_size] = 0;
		mapa.get_textMap()[std::make_pair(this->getX()/tile_size, this->getY()/tile_size)] = "porta_fechada";
	}
}
