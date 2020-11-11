#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "viewer.h"
#include "map.h"
#include "element.h"
#include "player.h"
#include "collisionController.h"
#include "camera_controller.h"
#include "camera.h"
#include "porta.h"
#include "porta_controller.h"
#include "eventos.h"


class Controller {
	private:
		std::shared_ptr<Viewer> viewer;
		std::shared_ptr<Eventos> event;
		std::shared_ptr<Map> map;
		std::shared_ptr<Player> player;
		std::shared_ptr<collisionController> collisioncontroller;

		std::shared_ptr<Camera_controller> cameracontroller;
		std::shared_ptr<Porta_controller> portacontroller;

		/* stores all cameras */
		std::vector<std::shared_ptr<Camera>> cameraVec;
		/* stores all portas */
		std::vector<std::shared_ptr<Porta>> portaVec;

  		const Uint8* state = NULL;
		bool rodando = true;
  		SDL_Event evento; // eventos discretos

		// porta timer
		int portaEventCounter = 0;
		int portaGo = 0;

		// sizes	
		int tileSize;
		/* tile subdivision */
		//int subdivisions = 1;
		/* bounding box size = tilesize/subdivisions */
		int boxSize;
	public:
		Controller();
		/* main game loop */
		void gameLoop();
		void titleScreen();
};
