#ifndef PLAYER_H
#define PLAYER_H

#include "element.h"
#include <iostream>

class Player : public Element {
	public:
		int frame = 0;
		int counter = 0;
		Player(int x, int y);
		int getFrame();	
		void setFrame(std::string s);	
};

#endif
