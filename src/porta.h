#ifndef PORTA_H
#define PORTA_H
#include "element.h"

class Porta : public Element{
	private:
		int flag;
	public:
		Porta(int x, int y);
		int get_flag();
		void set_flag(int flag);
};

#endif
