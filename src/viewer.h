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
		// Size of tile sides (tiles are squares)
		int tileSize;

		// Controlador:
		bool rodando = true;

		// Variaveis para verificar eventos
		SDL_Event evento; // eventos discretos

		const int SCREEN_WIDTH = 400;
		const int SCREEN_HEIGHT = 400;

		const Uint8* state = SDL_GetKeyboardState(nullptr); // estado do teclado

		//metodos
		Viewer();
		~Viewer();
		void render();
		void renderMap(std::map<std::pair<int, int>, std::string> textMap);
};
