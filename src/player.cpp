#include "player.h"

Player::Player(int x, int y){
    this->x = x;
    this->y = y;
}

Player::Player(int x, int y, int w, int h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

int Player::getFrame(){
	return frame;
}

void Player::setFrame(int frame){
	this->frame = frame;
}

void Player::setFrame(std::string s){
	if (s=="left"){
		// if the player was on a different direction, reset
		if (frame<6||frame>8){
			frame = 7;	
			counter=0;
		}
		// increment every 4 cycles
		else if(counter/4==1){
			if (frame == 6)
				frame+=2;
			else if (frame == 8)
				frame-=2;
			else if (frame == 7)
				frame++;
			counter=0;
		}
		else
			counter++;
	}
	if (s=="up"){
		if (frame>2){
			frame = 1;	
			counter=0;
		}
		else if(counter/4==1){
			if (frame == 0)
				frame+=2;
			else if (frame == 2)
				frame-=2;
			else if (frame == 1)
				frame++;
			counter=0;
		}
		else
			counter++;
	}
	if (s=="right"){
		if (frame<9){
			frame = 10;	
			counter=0;
		}
		else if(counter/4==1){
			if (frame == 9)
				frame+=2;
			else if (frame == 11)
				frame-=2;
			else if (frame == 10)
				frame++;
			counter=0;
		}
		else
			counter++;
	}
	if (s=="down"){
		if (frame<3||frame>5)	{
			frame = 4;	
			counter=0;
		}
		else if(counter/4==1){
			if (frame == 3)
				frame+=2;
			else if (frame == 5)
				frame-=2;
			else if (frame == 4)
				frame++;
			counter=0;
		}
		else
			counter++;
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
		counter=0;
	}
}
