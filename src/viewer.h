#ifndef VIEWER_H
#define VIEWER_H

#include <memory>
#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Viewer{
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;

		// Texture Dictionary
		std::map<std::string, SDL_Texture*> textDict;
		// Stores Texture Map
		std::map<std::pair<int, int>, std::string> textMap;
		// Size of tile sides (tiles are squares)
		SDL_Rect tileRect;
		// Size of player Texture
		SDL_Rect playerRect;
		// Variaveis para verificar eventos
		SDL_Event evento; // eventos discretos

		const int SCREEN_WIDTH = 200;
		const int SCREEN_HEIGHT = 200;

		const Uint8* state = SDL_GetKeyboardState(nullptr); // estado do teclado

		//metodos
		Viewer();
		~Viewer();
		void render();
		void updateMap(std::map<std::pair<int, int>, std::string> textMap);
		void updatePlayer(int x, int y);
};

#endif
