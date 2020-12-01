#include "element.h"

Element::Element(int x, int y){
    this->x = x;
    this->y = y;
}

void Element::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

void Element::setTextSize(int w, int h){
    this->w = w;
    this->h = h;
    boxSize = w;
}

int Element::getX(){return this->x;}
int Element::getY(){return this->y;}
int Element::getW(){return this->w;}
int Element::getH(){return this->h;}
int Element::getBoxSize(){return boxSize;}
