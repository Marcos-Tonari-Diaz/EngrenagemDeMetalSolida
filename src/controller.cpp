#include "controller.h"

Controller::Controller() : viewer(new Viewer), 
map(new Map("../assets/maps/map10x10.map")), 
player(new Player(0, 0)), 
collisioncontroller(new collisionController()
){
	// pass tilesize 
	tileSize = viewer->tileRect.w;
	boxSize = tileSize/subdivisions;
	map->setTileSize(tileSize);
	collisioncontroller->set_boundBoxSize(boxSize);
	collisioncontroller->set_tileSize(tileSize);
	player->setTextSize(boxSize, boxSize*(41/24));

	// configure keyboars state
  	state = SDL_GetKeyboardState(nullptr); 
	collisioncontroller->set_state(state);
	collisioncontroller->set_map(map);
	collisioncontroller->makeCollisionMap();

	// set element vectors
	map->setPortaVec(portaVec);
	map->setCameraVec(cameraVec);
}

/* main game loop*/
void Controller::gameLoop(){
	int flag;
	// render Map
	viewer->updateMap(map->get_textMap());	
	while(rodando){
		// Event Polling
		SDL_PumpEvents(); // Updates Keyboard State

		// Collision Control
		collisioncontroller->move(*player);
		//std::cout << player->getX() << ", " << player->getY() << std::endl;

		// Door Control
		for (int i = 0; i < portaVec.size(); i++){
			portacontroller->abre_fecha(*(portaVec[i]), *player, *map, state);
		}
		/*
		// Camera Control
		for (int i = 0; i < cameraVec.size(); i++){
			cameracontroller->visao(map, cameraVec[i], player);
			cameracontroller->deteccao(map, cameraVec[i], player);
		}
		// Events Control
		flag = checagem(player, portaVec, cameraVec);
		if(flag == 0) {
			// TEM QUE FAZER O JOGO VOLTAR PARA A TELA PRINCIPAL.... NAO SEI FAZER :c
		}
		*/
		// Rendering
		viewer->render(*player);

		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_QUIT) {
				rodando = false;
			}
		}
    	SDL_Delay(20);
	}		
}
