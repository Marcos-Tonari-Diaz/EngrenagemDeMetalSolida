#ifndef PLAYER_H
#define PLAYER_H

#include <string>

typedef struct {
	int x=20;
	int y=20;
} Position;

class Player {
	private:
		/*position in (x,y) coordinates*/
		Position pos; 		
	public:
		Player();
		Position& get_position();
};

#endif
