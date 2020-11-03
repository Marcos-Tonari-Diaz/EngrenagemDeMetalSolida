#include "controller.h"

Controller::Controller() : viewer(new Viewer), map(new Map("../assets/maps/test.map")), player(new Player) {
	
}

/* main game loop*/
void Controller::gameLoop(){
	// render Map
	viewer->renderMap(map->get_textMap());	
	// Players move in 1/4 tile size steps
	step = viewer->tileRect.w/4;
	while(rodando){
		// Event Polling
		SDL_PumpEvents(); // Updates Keyboard State
		// updates player position
		if (state[SDL_SCANCODE_LEFT]) player->get_position().x -= step;
		if (state[SDL_SCANCODE_RIGHT]) player->get_position().x += step;
		if (state[SDL_SCANCODE_UP]) player->get_position().y -= step;
		if (state[SDL_SCANCODE_DOWN]) player->get_position().y += step;

		viewer->renderPlayer(player->get_position().x, player->get_position().y);

		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_QUIT) {
				rodando = false;
			}
		}
    	SDL_Delay(20);
	}		
}
