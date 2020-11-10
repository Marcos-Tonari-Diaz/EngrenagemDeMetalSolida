#include "porta.h"
#include "element.h"

Porta::Porta(int x, int y) {
	this->setPosition(x, y);
	this->flag = 0;
}

int Porta::get_flag() {
	return (this->flag);
}

void Porta::set_flag(int flag) {
	this->flag = flag;
}
