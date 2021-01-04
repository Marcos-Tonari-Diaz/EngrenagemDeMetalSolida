#include "controller.h"

Controller::Controller() : viewer(new Viewer), 
			player(new Player(0, 0)), 
			collisioncontroller(new collisionController()),
			portacontroller(new Porta_controller()),
			slcontroller(new SLcontroller()),
			trcontroller(new TRcontroller()),
			cameracontroller(new Camera_controller()),
			event(new Eventos())
{
	// create the 4 maps
	mapVec.push_back(std::shared_ptr<Map> (new Map(0)));
	mapVec.push_back(std::shared_ptr<Map> (new Map(1)));
	mapVec.push_back(std::shared_ptr<Map> (new Map(2)));
	mapVec.push_back(std::shared_ptr<Map> (new Map(3)));

	// pass tilesize and bounding box size
	tileSize = viewer->tileRect.w;
	boxSize = tileSize - tileSize/4;
	mapVec[0]->setTileSize(tileSize);
	mapVec[1]->setTileSize(tileSize);
	mapVec[2]->setTileSize(tileSize);
	mapVec[3]->setTileSize(tileSize);

	// character ounding box height
	int boundBoxH = (int) ((float) boxSize*((float) 41/24));
	player->setTextSize(boxSize, boundBoxH);
	player->setPosition(3*tileSize, 3*tileSize);
	collisioncontroller->set_boundBoxSize(boxSize, boundBoxH);
	collisioncontroller->set_tileSize(tileSize);
	portacontroller->setTileSize(tileSize);
	portacontroller->setBoundBoxSize(boxSize);
	cameracontroller->setTileSize(tileSize);
	cameracontroller->setBoundBoxSize(boxSize);
	event->setTileSize(tileSize);

	// configure keyboard state
  	state = SDL_GetKeyboardState(nullptr); 
	collisioncontroller->set_state(state);

	// load Map
	mapVec[0]->loadMap("../assets/maps/m0.map");
	mapVec[1]->loadMap("../assets/maps/m1.map");
	mapVec[2]->loadMap("../assets/maps/m2.map");
	mapVec[3]->loadMap("../assets/maps/m3.map");


	// allocate new elements
	for (int i=0; i < mapVec[0]->getHeight(); i++){
		for (int j=0; j < mapVec[0]->getWidth(); j++){
			// for each map
			for (int k=0; k<4; k++){
				// sets map start tile 
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="start")
					event->setStart(j*tileSize,i*tileSize, k);

				// sets game end tile (destination)
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="end")
					event->setEnd(j*tileSize,i*tileSize, k);

				// sets next room tile (destination)
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="to0")
					event->setNext(j*tileSize,i*tileSize, k, 0);
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="to1")
					event->setNext(j*tileSize,i*tileSize, k, 1);
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="to2")
					event->setNext(j*tileSize,i*tileSize, k, 2);
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="to3")
					event->setNext(j*tileSize,i*tileSize, k, 3);

				// allocattes a new porta
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="porta_fechada")
					portaVec.push_back(std::shared_ptr<Porta> (new Porta(j*tileSize,i*tileSize, 0, k)));
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="porta_aberta")
					portaVec.push_back(std::shared_ptr<Porta> (new Porta(j*tileSize,i*tileSize, 1, k)));

				// allocattes a new camera
				int alcance = tileSize*2;
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="camera_cima")
					cameraVec.push_back(std::shared_ptr<Camera> (new Camera(0, alcance, j*tileSize,i*tileSize, k)));
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="camera_baixo")
					cameraVec.push_back(std::shared_ptr<Camera> (new Camera(1, alcance, j*tileSize,i*tileSize, k)));
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="camera_direita")
					cameraVec.push_back(std::shared_ptr<Camera> (new Camera(2, alcance, j*tileSize,i*tileSize, k)));
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="camera_esquerda")
					cameraVec.push_back(std::shared_ptr<Camera> (new Camera(3, alcance, j*tileSize,i*tileSize, k)));
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="camera_cima_direita")
					cameraVec.push_back(std::shared_ptr<Camera> (new Camera(6, alcance, j*tileSize,i*tileSize, k)));
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="camera_cima_esquerda")
					cameraVec.push_back(std::shared_ptr<Camera> (new Camera(7, alcance, j*tileSize,i*tileSize, k)));
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="camera_baixo_direita")
					cameraVec.push_back(std::shared_ptr<Camera> (new Camera(4, alcance, j*tileSize,i*tileSize, k)));
				if (mapVec[k]->get_textMap()[std::make_pair(j,i)]=="camera_baixo_esquerda")
					cameraVec.push_back(std::shared_ptr<Camera> (new Camera(5, alcance, j*tileSize,i*tileSize, k)));
			}
		}
	}
	// mapa inicial
	collisioncontroller->set_map(mapVec[0]);
	viewer->updateMap(mapVec[0]->get_textMap());	
	player->setCurrentMap(0);
}

/* monitor loop*/
void Controller::monitorLoop(){
	std::cout << "Monitor mode" << std::endl;
	//int transmission = 0;
	std::string str;

	// Configurar o Cliente
	trcontroller->configClient();

	while(rodando){
		// Load Received State
		json stateJSON = trcontroller->receiveState();
		str.push_back('y'); str.push_back('1');
		slcontroller->load(stateJSON, *player, str);
		str.pop_back(); str.pop_back();
		for (int i = 0; i < portaVec.size(); i++){
			str.push_back('p'); str.push_back(i);
			slcontroller->load(stateJSON, *(portaVec[i]), str);
			str.pop_back(); str.pop_back();
			portaVec[i]->atualiza_porta(collisioncontroller->getCollisionMap(), tileSize, *mapVec[player->getCurrentMap()]);
		}
		for (int i = 0; i < cameraVec.size(); i++){
			str.push_back('c'); str.push_back(i);
			slcontroller->load(stateJSON, *(cameraVec[i]), str);
			str.pop_back(); str.pop_back();
		}
		std::cout << "Monitor State Loaded!" <<std::endl; 
		// Rendering
		viewer->updateMap(mapVec[player->getCurrentMap()]->get_textMap());	
		viewer->render(*player);

		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_QUIT) {
				rodando = false;
			}
		}
    	SDL_Delay(20);
	}
}

/* main game loop*/
void Controller::gameLoop(){
	std::cout << "Game mode" << std::endl;
	// event flag
	int flag = 0;
	//int transmission = 0;
	// auxiliary string for load/save
	std::string str;

	// Configurar o Server
	trcontroller->configServer();

	// Start at title screen
	//titleScreen();
	while(rodando){
		// mapa inicial
		collisioncontroller->set_map(mapVec[player->getCurrentMap()]);

		// Event Polling
		SDL_PumpEvents(); // Updates Keyboard State

		// Movement and Collision Control
		collisioncontroller->move(*player);

		// Door Control
		// reset timer
		if (buttonReady && state[SDL_SCANCODE_E]){
			for (int i = 0; i < portaVec.size(); i++){
				portacontroller->abre_fecha(*(portaVec[i]), *player, *mapVec[player->getCurrentMap()], state, collisioncontroller->getCollisionMap());
			}
			// if "e" was pressed, start counting again
			if (state[SDL_SCANCODE_E]){
				buttonEventCounter++;
				buttonReady = 0;
			}
		}
		
		// Save Current State
		if(buttonReady && state[SDL_SCANCODE_S]) {
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
				buttonEventCounter++;
				buttonReady = 0;
			}
			slcontroller->save();
			std::cout << "Saved!" <<std::endl;
		}
		
		// Load Saved File
		if(buttonReady && state[SDL_SCANCODE_L]) {
			str.push_back('y'); str.push_back('1');
			slcontroller->load(*player, str);
			str.pop_back(); str.pop_back();
			for (int i = 0; i < portaVec.size(); i++){
				str.push_back('p'); str.push_back(i);
				slcontroller->load(*(portaVec[i]), str);
				str.pop_back(); str.pop_back();
				portaVec[i]->atualiza_porta(collisioncontroller->getCollisionMap(), tileSize, *mapVec[player->getCurrentMap()]);
			}
			for (int i = 0; i < cameraVec.size(); i++){
				str.push_back('c'); str.push_back(i);
				slcontroller->load(*(cameraVec[i]), str);
				str.pop_back(); str.pop_back();
			}
			if (state[SDL_SCANCODE_L]){
				buttonEventCounter++;
				buttonReady = 0;
			}
			std::cout << "Loaded!" <<std::endl;
		}
		
		// increment reset timer
		buttonEventCounter = (buttonEventCounter+1)%40;
		if (buttonEventCounter==0){buttonReady = 1;}

		// Camera Control
		for (int i = 0; i < cameraVec.size(); i++){
			cameracontroller->visao(*mapVec[player->getCurrentMap()], (*cameraVec[i]), *player);
			cameracontroller->deteccao(*mapVec[player->getCurrentMap()], (*cameraVec[i]), *player);
		}

		// Events Control
		flag = event->checagem(*player);
		// mudanca de mapa
		if(flag>=0 && flag<=3) {
		}
		// fim do jogo
		if(flag == 4) {
			//titleScreen();
		}
		for (int i = 0; i < cameraVec.size(); i++){
			flag = event->checagem(*player, *(cameraVec[i]));
			// avistado pela camera (spawn no mapa 0)
			if(flag == 5) {
				viewer->renderExclamation(*(cameraVec[i]));
				for (int i = 0; i < portaVec.size(); i++){
					portaVec[i]->set_flag(0);
					portaVec[i]->atualiza_porta(collisioncontroller->getCollisionMap(), tileSize, *mapVec[player->getCurrentMap()]);
				}
				break;
			}
		}

		// Save in file to transfer to viwer
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
		//if(state[SDL_SCANCODE_T]) transmission = 1;
		//if(transmission) trcontroller->sendState(slcontroller->get_file());
		trcontroller->sendState(slcontroller->get_file());

		// Rendering
		viewer->updateMap(mapVec[player->getCurrentMap()]->get_textMap());	
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
