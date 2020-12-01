#include "controller.h"

Controller::Controller() : viewer(new Viewer), 
map(new Map()), 
player(new Player(0, 0)), 
collisioncontroller(new collisionController()),
portacontroller(new Porta_controller()),
slcontroller(new SLcontroller()),
cameracontroller(new Camera_controller()),
event(new Eventos())
{
	// pass tilesize 
	tileSize = viewer->tileRect.w;
	boxSize = tileSize - tileSize/4;
	map->setTileSize(tileSize);
	collisioncontroller->set_boundBoxSize(boxSize);
	collisioncontroller->set_tileSize(tileSize);
	player->setTextSize(boxSize, boxSize*(41/24));
	portacontroller->setTileSize(tileSize);
	portacontroller->setBoundBoxSize(boxSize);
	cameracontroller->setTileSize(tileSize);
	cameracontroller->setBoundBoxSize(boxSize);

	// configure keyboard state
  	state = SDL_GetKeyboardState(nullptr); 
	collisioncontroller->set_state(state);

	// load Map
	map->loadMap("../assets/maps/map10x10.map");
	collisioncontroller->set_map(map);

	// allocate new elements
	for (int i=0; i < map->getHeight(); i++){
		for (int j=0; j < map->getWidth(); j++){
			// sets end tile (destination)
			if (map->get_textMap()[std::make_pair(j,i)]=="end")
				event->setEnd(j*tileSize,i*tileSize);
			// allocattes a new porta
			if (map->get_textMap()[std::make_pair(j,i)]=="porta_fechada")
				portaVec.push_back(std::shared_ptr<Porta> (new Porta(j*tileSize,i*tileSize, 0)));
			if (map->get_textMap()[std::make_pair(j,i)]=="porta_aberta")
				portaVec.push_back(std::shared_ptr<Porta> (new Porta(j*tileSize,i*tileSize, 1)));

			// allocattes a new camera
			int alcance = tileSize*2;
			if (map->get_textMap()[std::make_pair(j,i)]=="camera_cima")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(0, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(j,i)]=="camera_baixo")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(1, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(j,i)]=="camera_direita")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(2, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(j,i)]=="camera_esquerda")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(3, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(j,i)]=="camera_cima_direita")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(6, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(j,i)]=="camera_cima_esquerda")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(7, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(j,i)]=="camera_baixo_direita")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(4, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(j,i)]=="camera_baixo_esquerda")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(5, alcance, j*tileSize,i*tileSize)));
		}
	}
	// register map in viewer
	viewer->updateMap(map->get_textMap());	
}

/* main game loop*/
void Controller::gameLoop(){
	int flag = 0;
	std::string str;
	titleScreen();
	while(rodando){
		// Event Polling
		SDL_PumpEvents(); // Updates Keyboard State

		// Collision Control
		collisioncontroller->move(*player);

		//std::cout <<portaVec.size()<<std::endl;

		// Door Control
		// reset timer
		if (portaGo && state[SDL_SCANCODE_E]){
			for (int i = 0; i < portaVec.size(); i++){
				portacontroller->abre_fecha(*(portaVec[i]), *player, *map, state, collisioncontroller->getCollisionMap());
			}
			// if "e" was pressed, start counting again
			if (state[SDL_SCANCODE_E]){
				portaEventCounter++;
				portaGo = 0;
			}
		}
		
		// Save Current State
		if(portaGo && state[SDL_SCANCODE_S]) {
			str.push_back('y'); str.push_back('1');
			slcontroller->add(*player, str);
			str.pop_back(); str.pop_back();
			for (int i = 0; i < portaVec.size(); i++){
				str.push_back('p'); str.push_back(i);
				slcontroller->add(*(portaVec[i]), str);
				str.pop_back(); str.pop_back();
			}
			for (int i = 0; i < cameraVec.size(); i++){
				str.push_back('c'); str.push_back(i);
				slcontroller->add(*(cameraVec[i]), str);
				str.pop_back(); str.pop_back();
			}
			if (state[SDL_SCANCODE_S]){
				portaEventCounter++;
				portaGo = 0;
			}
			slcontroller->save();
		}
		
		// Load Saved File
		if(portaGo && state[SDL_SCANCODE_L]) {
			str.push_back('y'); str.push_back('1');
			slcontroller->load(*player, str);
			str.pop_back(); str.pop_back();
			for (int i = 0; i < portaVec.size(); i++){
				str.push_back('p'); str.push_back(i);
				slcontroller->load(*(portaVec[i]), str);
				str.pop_back(); str.pop_back();
				portaVec[i]->atualiza_porta(collisioncontroller->getCollisionMap(), tileSize, *map);
			}
			for (int i = 0; i < cameraVec.size(); i++){
				str.push_back('c'); str.push_back(i);
				slcontroller->load(*(cameraVec[i]), str);
				str.pop_back(); str.pop_back();
			}
			if (state[SDL_SCANCODE_L]){
				portaEventCounter++;
				portaGo = 0;
			}
		}
		
		// increment reset timer
		portaEventCounter = (portaEventCounter+1)%40;
		if (portaEventCounter==0){portaGo = 1;}

		// Camera Control
		for (int i = 0; i < cameraVec.size(); i++){
			cameracontroller->visao(*map, (*cameraVec[i]), *player);
			cameracontroller->deteccao(*map, (*cameraVec[i]), *player);
		}

		// Events Control
		for (int i = 0; i < cameraVec.size(); i++){
			flag = event->checagem(*player, *(cameraVec[i]), tileSize, boxSize);
			if(flag == 0) {
				titleScreen();
				player->setPosition(0,0);
				break;
			}
			if(flag == 2) {
				viewer->renderExclamation(*(cameraVec[i]));
				player->setPosition(0,0);
				for (int i = 0; i < portaVec.size(); i++){
					portaVec[i]->set_flag(0);
					portaVec[i]->atualiza_porta(collisioncontroller->getCollisionMap(), tileSize, *map);
				}
				break;
			}
		}

		// Rendering
		viewer->updateMap(map->get_textMap());	
		viewer->render(*player);

		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_QUIT) {
				rodando = false;
			}
		}
    	SDL_Delay(20);
	}		
}

void Controller::titleScreen(){
	int title = 0;
	player->setPosition(0,0);
	viewer->renderMain();
	while (!title){
		while (SDL_PollEvent(&evento)){
			break;
		}
		if (evento.type == SDL_KEYDOWN && evento.key.keysym.scancode == SDL_SCANCODE_SPACE)
			title = 1;
	}
	return;
}
