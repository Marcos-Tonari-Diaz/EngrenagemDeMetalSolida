#ifndef VIEWER_H
#define VIEWER_H

#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.h"

class Viewer{
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;

		// TileSheets
		SDL_Texture* bgTiles;
		SDL_Texture* doorTiles;
		SDL_Texture* testTile;
		SDL_Texture* playerSheet;

		// Player Animation Sprites Rectangles
		std::vector<SDL_Rect*> playerSprites;

		// Tile Source Rectangles
		SDL_Rect wallRect; 
		SDL_Rect corridorRect; 
		SDL_Rect portaFechadaRect; 
		SDL_Rect portaAbertaRect; 
		SDL_Rect cameraCimaRect; 
		SDL_Rect cameraCimaDirRect; 
		SDL_Rect cameraCimaEsqRect; 
		SDL_Rect cameraBaixoRect; 
		SDL_Rect cameraBaixoDirRect; 
		SDL_Rect cameraBaixoEsqRect; 
		SDL_Rect cameraEsqRect; 
		SDL_Rect cameraDirRect; 

		// Texture Dictionary
		std::map<std::string, std::pair<SDL_Texture*, SDL_Rect*>> textDict;

		// Reference to Texture Map
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
