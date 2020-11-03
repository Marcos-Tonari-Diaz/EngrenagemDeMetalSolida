#include <memory>
#include "viewer.h"
#include "map.h"
#include "player.h"
#include <SDL2/SDL.h>

class Controller {
	private:
		std::shared_ptr<Viewer> viewer;
		std::shared_ptr<Map> map;
		std::shared_ptr<Player> player;

		bool rodando = true;
  		const Uint8* state = SDL_GetKeyboardState(nullptr); // estado do teclado
  		SDL_Event evento; // eventos discretos
		int step;
	public:
		Controller();
		void gameLoop();
};
