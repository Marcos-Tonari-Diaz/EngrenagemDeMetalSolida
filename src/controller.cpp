#include "controller.h"

Controller::Controller() : viewer(new Viewer), 
map(new Map()), 
player(new Player(0, 0)), 
collisioncontroller(new collisionController()),
portacontroller(new Porta_controller()),
cameracontroller(new Camera_controller())
{
	// pass tilesize 
	tileSize = viewer->tileRect.w;
	boxSize = tileSize/subdivisions;
	map->setTileSize(tileSize);
	collisioncontroller->set_boundBoxSize(boxSize);
	collisioncontroller->set_tileSize(tileSize);
	player->setTextSize(boxSize, boxSize*(41/24));
	portacontroller->setTileSize(tileSize);
	portacontroller->setBoundBoxSize(boxSize);

	// configure keyboars state
  	state = SDL_GetKeyboardState(nullptr); 
	collisioncontroller->set_state(state);

	// load Map
	map->loadMap("../assets/maps/map10x10.map");
	collisioncontroller->set_map(map);

	// allocate new elements
	for (int i=0; i < map->getHeight(); i++){
		for (int j=0; j < map->getWidth(); j++){
			// allocattes a new porta
			if (map->get_textMap()[std::make_pair(i,j)]=="porta_fechada")
				portaVec.push_back(std::shared_ptr<Porta> (new Porta(j*tileSize,i*tileSize, 0)));
			if (map->get_textMap()[std::make_pair(i,j)]=="porta_aberta")
				portaVec.push_back(std::shared_ptr<Porta> (new Porta(j*tileSize,i*tileSize, 1)));

			// allocattes a new camera
			int alcance = 1;
			if (map->get_textMap()[std::make_pair(i,j)]=="camera_cima")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(0, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(i,j)]=="camera_baixo")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(1, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(i,j)]=="camera_direita")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(2, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(i,j)]=="camera_esquerda")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(3, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(i,j)]=="camera_cima_direita")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(4, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(i,j)]=="camera_cima_esquerda")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(5, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(i,j)]=="camera_baixo_direita")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(6, alcance, j*tileSize,i*tileSize)));
			if (map->get_textMap()[std::make_pair(i,j)]=="camera_baixo_esquerda")
				cameraVec.push_back(std::shared_ptr<Camera> (new Camera(7, alcance, j*tileSize,i*tileSize)));
		}
	}
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

		//std::cout <<portaVec.size()<<std::endl;
		// Door Control
		/*
		for (int i = 0; i < portaVec.size(); i++){
			portacontroller->abre_fecha(*(portaVec[i]), *player, *map, state);
		}
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
