#include <memory>
#include "viewer.h"
#include "map.h"
#include "player.h"
#include "collisionController.h"
#include <SDL2/SDL.h>

class Controller {
	private:
		std::shared_ptr<Viewer> viewer;
		std::shared_ptr<Map> map;
		std::shared_ptr<Player> player;
		//std::shared_ptr<collisionController> collisioncontroller;

  		const Uint8* state = SDL_GetKeyboardState(nullptr); // estado do teclado
		bool rodando = true;
  		SDL_Event evento; // eventos discretos
		int step;
	public:
		Controller();
		void gameLoop();
};
