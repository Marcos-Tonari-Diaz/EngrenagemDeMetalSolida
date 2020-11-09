#include "controller.h"

Controller::Controller() : viewer(new Viewer), map(new Map("../assets/maps/test.map")), player(new Player(0,0)), collisioncontroller(new collisionController()){
	tileSize = viewer->tileRect.w;
	player->setTileSize(tilesize);
	// configure keyboars state
  	state = SDL_GetKeyboardState(nullptr); 
	collisioncontroller->set_state(state);
	collisioncontroller->set_map(map);
	// defines size of collision bounding boxes
	collisioncontroller->makeCollisionMap();
	// pass tilesize to player
	player->setTileSize(tilesize, tilesize);
}

/* main game loop*/
void Controller::gameLoop(){
	// render Map
	viewer->updateMap(map->get_textMap());	
	while(rodando){
		// Event Polling
		SDL_PumpEvents(); // Updates Keyboard State
		collisioncontroller->move(*player);
		std::cout << player->getX() << ", " << player->getY() << std::endl;
		//std::cout << player->getX() << ", " << player->getY() << std::endl;
		viewer->render(*player);

		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_QUIT) {
				rodando = false;
			}
		}
    	SDL_Delay(20);
	}		
}
