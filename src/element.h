#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Element{
    protected:
        int x = 0;
        int y = 0;
        std::string textureKey = "";
	SDL_Rect rect;
	int tileHeight = 0;
	int tileWidth = 0;
    public:
        Element() = default;
        Element(int x, int y, std::string textureKey);
        int getX();
        int getY();
	int getTileHeight();
	int getTileWidth();
        void setPosition(int x, int y);
	void setTileSize(int w, int h);
        std::string getTextureKey();
	SDL_Rect* getRect();
};

#endif
