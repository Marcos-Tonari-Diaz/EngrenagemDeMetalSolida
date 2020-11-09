#include "element.h"

Element::Element(int x, int y){
    textRect.x = x;
    textRect.y = y;
}

void Element::setPosition(int x, int y){
    textRect.x = x;
    textRect.y = y;
}

void Element::setTextSize(int w, int h){
    textRect.w = w;
    textRect.h = h;
    boxSize = w;
}

int Element::getX(){return textRect.x;}
int Element::getY(){return textRect.y;}
int Element::getBoxSize(){return boxSize;}

SDL_Rect* Element::getRect(){return &textRect;}
