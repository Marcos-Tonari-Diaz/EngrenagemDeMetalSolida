#include "controller.h"

Controller::Controller() : viewer(new Viewer), 
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

	// character bounding box height
	int boundBoxH = (int) ((float) boxSize*((float) 41/24));
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
}

/* monitor loop*/
void Controller::monitorLoop(){
	std::cout << "Monitor mode" << std::endl;
	//int transmission = 0;
	std::string str;

	// Configurar o Cliente
	trcontroller->configClient();

	// Garbage command to initiate
	std::string init= "D";
	trcontroller->sendJSON(init);
	while(rodando){
		// increment reset timer
		buttonEventCounter = (buttonEventCounter+1)%40;
		if (buttonEventCounter==0){buttonReady = 1;}

		// for all players
		// Load Received State
		json stateJSON = trcontroller->receiveJSON();
		std::cout << "recebeu estado" << std::endl;
		for (int ouo = 0; ouo < ; ouo++) {
			str.push_back('y'); str.push_back('1');
			slcontroller->load(stateJSON, *(players[ouo]), str);
			str.pop_back(); str.pop_back();
		}
		for (int i = 0; i < portaVec.size(); i++){
			str.push_back('p'); str.push_back(i);
			slcontroller->load(stateJSON, *(portaVec[i]), str);
			str.pop_back(); str.pop_back();
			portaVec[i]->atualiza_porta(collisioncontroller->getCollisionMap(), tileSize, *mapVec[players[trcontroller->player_number-1]->getCurrentMap()]);
		}
		for (int i = 0; i < cameraVec.size(); i++){
			str.push_back('c'); str.push_back(i);
			slcontroller->load(stateJSON, *(cameraVec[i]), str);
			str.pop_back(); str.pop_back();
		}
		std::cout << "Monitor State Loaded!" <<std::endl; 
		std::cout << players.size() <<std::endl; 
		// Rendering
		viewer->updateMap(mapVec[players[trcontroller->player_number-1]->getCurrentMap()]->get_textMap());	
		//viewer->updateMap(mapVec[0]->get_textMap());	
		std::cout << "updated map" <<std::endl; 
		viewer->render(players);

		// Send Player Input 
		if(buttonReady && state[SDL_SCANCODE_UP]) {
			str= "U";
			trcontroller->sendString(str);
			if (state[SDL_SCANCODE_UP]){
				buttonEventCounter++;
				buttonReady = 0;
			}
		}

		if(buttonReady && state[SDL_SCANCODE_LEFT]) {
			str ="L";
			trcontroller->sendString(str);
			if (state[SDL_SCANCODE_LEFT]){
				buttonEventCounter++;
				buttonReady = 0;
			}
		}
				
		if(buttonReady && state[SDL_SCANCODE_RIGHT]) {
			str = "R";
			trcontroller->sendString(str);
			if (state[SDL_SCANCODE_RIGHT]){
				buttonEventCounter++;
				buttonReady = 0;
			}
		}

		if(buttonReady && state[SDL_SCANCODE_DOWN]) {
			str= "D";
			trcontroller->sendString(str);
			if (state[SDL_SCANCODE_DOWN]){
				buttonEventCounter++;
				buttonReady = 0;
			}
		}


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
	// Setting boundBox
	int boundBoxH = (int) ((float) boxSize*((float) 41/24));
	// event flag
	int flag = 0;
	//int transmission = 0;
	// auxiliary string for load/save
	std::string str;
	//chars de comparaçao
	char m[] = "\0"; char n[] = "\n"; char nove[] = "9";
	int Por; int Up; int Down; int Left; int Right;
	
	// Configurar o Server
	trcontroller->configServer(); // NAO SEI O QUE ISSO FAZ, E SE ISSO ATRAPALHA NO Q EU FIZ

	// Thread for reciving clients and information
	std::thread connection (&TRcontroller::checkConnection, trcontroller, 0);

	// Start at title screen
	//titleScreen();
	while(rodando){
		for (int ouo = 0; ouo < ((trcontroller->get_commands()).size()); ouo++) {
		//std::cout << trcontroller->get_commands()[ouo] << std::endl;
			// Player has entered the server
			if(strcmp(m, (trcontroller->get_commands())[ouo]) == 0) {
				players.push_back(std::shared_ptr<Player> (new Player(0, 0)));
				((trcontroller->get_commands())[ouo]) = "9";
				players[ouo]->setTextSize(boxSize, boundBoxH);
				players[ouo]->setPosition(3*tileSize, 3*tileSize);
				players[ouo]->setCurrentMap(0);
			}

			// Player has left the server
			else if(strcmp(n, (trcontroller->get_commands())[ouo]) == 0) {
				players.erase(players.begin() + ouo);
				(trcontroller->get_commands()).erase((trcontroller->get_commands()).begin() + ouo);
			}

			// In case player in position "ouo" hasn't sent more commands
			else if(strcmp(nove, (trcontroller->get_commands())[ouo]) == 0){
			       	continue;
			}

			// Processing commands from player in position "ouo"
			else {
				// Setting command flags
				Por = 0; Up = 0; Down = 0; Left = 0; Right = 0;
				if (((trcontroller->get_commands())[ouo]) == "E") Por = 1;
				else if (((trcontroller->get_commands())[ouo]) == "U") Up = 1;
				else if (((trcontroller->get_commands())[ouo]) == "D") Down = 1;
				else if (((trcontroller->get_commands())[ouo]) == "L") Left = 1;
				else if (((trcontroller->get_commands())[ouo]) == "R") Right = 1;
				((trcontroller->get_commands())[ouo]) = "9";

				// mapa inicial
				collisioncontroller->set_map(mapVec[players[ouo]->getCurrentMap()]);

				// Event Polling
				SDL_PumpEvents(); // Updates Keyboard State

				// Movement and Collision Control
				collisioncontroller->move(*(players[ouo]), Up, Down, Left, Right);

				// Door Control
				// reset timer
				if (Por){
					for (int i = 0; i < portaVec.size(); i++){
						portacontroller->abre_fecha(*(portaVec[i]), *(players[ouo]), *mapVec[players[ouo]->getCurrentMap()], state, collisioncontroller->getCollisionMap());
					}
				}

				// Camera Control
				for (int i = 0; i < cameraVec.size(); i++){
					cameracontroller->visao(*mapVec[players[ouo]->getCurrentMap()], (*cameraVec[i]), *(players[ouo]));
					cameracontroller->deteccao(*mapVec[players[ouo]->getCurrentMap()], (*cameraVec[i]), *(players[ouo]));
				}

				// Events Control
				flag = event->checagem(*(players[ouo]));
				// mudanca de mapa
				if(flag>=0 && flag<=3) {
				}
				// fim do jogo
				if(flag == 4) {
					//titleScreen();
				}
				for (int i = 0; i < cameraVec.size(); i++){
					flag = event->checagem(*(players[ouo]), *(cameraVec[i]));
					// avistado pela camera (spawn no mapa 0)
					if(flag == 5) {
						viewer->renderExclamation(*(cameraVec[i]));
						for (int i = 0; i < portaVec.size(); i++){
							portaVec[i]->set_flag(0);
							portaVec[i]->atualiza_porta(collisioncontroller->getCollisionMap(), tileSize, *mapVec[players[ouo]->getCurrentMap()]);
						}
						break;
					}
				}

				// Save in file to transfer to viwer
				for (int i = 0; i < players.size(); i++){
					str.push_back('y'); str.push_back(i);
					slcontroller->add(*(players[i]), str);
					str.pop_back(); str.pop_back();
				}
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
				std::cout << slcontroller->get_file() << std::endl;
				trcontroller->sendState_server(slcontroller->get_file());

				// Rendering
				//viewer->updateMap(mapVec[player->getCurrentMap()]->get_textMap());	
				//viewer->render(*player);

				while (SDL_PollEvent(&evento)) {
					if (evento.type == SDL_QUIT) {
						rodando = false;
					}
				}
				SDL_Delay(20);
			}
		}
	}
	trcontroller->set_flag(0);
	connection.join();
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
