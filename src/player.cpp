#include "player.h"

Player::Player(int x, int y){
    textRect.x = x;
    textRect.y = y;
}

int Player::getFrame(){
	return frame;
}

void Player::setFrame(std::string s){
	if (s=="left"){
		// if the player was on a different direction, reset
		if (frame<6||frame>=8)	
			frame = 7;	
		// increment
		else
			frame++;
	}
	if (s=="up"){
		if (frame>=2)	
			frame = 1;	
		else
			frame++;
	}
	if (s=="right"){
		if (frame<9 || frame == 11)	
			frame = 10;	
		else
			frame++;
	}
	if (s=="down"){
		if (frame<3||frame>=5)	
			frame = 4;	
		else
			frame++;
	}
	if (s=="iddle"){
		if (frame>=6 && frame<=8)
			frame = 7;	
		if (frame<=2)	
			frame = 1;	
		if (frame>=9)
			frame = 10;	
		if (frame>=3 && frame<=5)
			frame = 4;	
		

	}
	

}
