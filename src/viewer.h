#ifndef VIEWER_H
#define VIEWER_H

#include <memory>
#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.h"

class Viewer{
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;

		// TileSheets
		SDL_Texture* bgTiles;
		// Tile Source Retangles
		SDL_Rect wallRect; 
		SDL_Rect corridorRect; 
		// Texture Dictionary
		std::map<std::string, std::pair<SDL_Texture*, SDL_Rect*>> textDict;
		// Stores Texture Map
		std::map<std::pair<int, int>, std::string> textMap;
		// Size of tile sides (tiles are squares)
		// OBS: tileRec.w is global tilesize
		SDL_Rect tileRect;
		// Variaveis para verificar eventos
		SDL_Event evento; // eventos discretos
		int tileSize = 72;

		const int SCREEN_WIDTH = 10*tileSize;
		const int SCREEN_HEIGHT = 10*tileSize;

		const Uint8* state = SDL_GetKeyboardState(nullptr); // estado do teclado

		//metodos
		Viewer();
		~Viewer();
		void render(Player& player);
		void updateMap(std::map<std::pair<int, int>, std::string>& textMap);
};

#endif
