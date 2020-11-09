#ifndef PLAYER_H
#define PLAYER_H

#include "element.h"

class Player : public Element {
	public:
		int state=0;
		Player(int x, int y);
};

#endif
