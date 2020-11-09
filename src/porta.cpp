#include "porta.h"

Porta::Porta(int x, int y) {
	this->x = x;
	this->y = y;
	this->flag = 0;
}

int Porta::get_flag() {
	return (this->flag);
}

void Porta::set_flag(int flag) {
	this->flag = flag;
}
