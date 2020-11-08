#include "element.h"

Element::Element(int x, int y, std::string textureKey){
    this->x = x;
    this->y = y;
    this->textureKey = textureKey;
}

void Element::setPosition(int x, int y){
	this->x = x; 
	this->y = y;
	rect.x = x;
	rect.y = y;
}

void Element::setTileSize(int w, int h){
	tileHeight = h;
	tileWidth = w;
}

int Element::getX(){return x;}
int Element::getY(){return y;}
int Element::getTileHeight(){return tileHeight;}
int Element::getTileWidth(){return tileWidth;}

SDL_Rect* Element::getRect(){return &rect;}

std::string Element::getTextureKey(){return textureKey;}
