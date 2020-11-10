#ifndef PLAYER_H
#define PLAYER_H

#include "element.h"

class Player : public Element {
	public:
		int frame = 0;
		Player(int x, int y);
		int getFrame();	
		void setFrame(std::string s);	
};

#endif
