#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Element{
    protected:
	/* rectangle yo copy texture into */
	SDL_Rect textRect;
	/* size of bounding boz size = textRect wodth*/
	int boxSize;
    public:
        Element(int x, int y);
        int getX();
        int getY();
	itn getBoxSize();
        void setPosition(int x, int y);
	void setTileSize(int w, int h);
	SDL_Rect* getRect();
};

#endif
