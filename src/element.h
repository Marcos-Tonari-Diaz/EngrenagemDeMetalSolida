#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Element{
    protected:
	// position and size of element texture
	SDL_Rect rect;
    public:
        Element() = default;
        Element(int x, int y, std::string textureKey);
        int getX();
        int getY();
	int getTileHeight();
	int getTileWidth();
        void setPosition(int x, int y);
	void setTileSize(int w, int h);
	SDL_Rect* getRect();
};

#endif
