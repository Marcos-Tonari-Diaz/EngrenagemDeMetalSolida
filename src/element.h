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
        Element() = default;
        Element(int x, int y);
        int getX();
        int getY();
	int getBoxSize();
        void setPosition(int x, int y);
	void setTextSize(int w, int h);
	SDL_Rect* getRect();
};

#endif
