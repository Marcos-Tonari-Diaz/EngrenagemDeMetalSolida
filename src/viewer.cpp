#include "viewer.h"

Viewer::Viewer(): generator(5), corrDistr(1,0.25), wallDist(4,0.25) {
  // Inicializando o subsistema de video do SDL
  try{
	  if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
	    std::cout << SDL_GetError();
	    throw 1;
	  }

	  // Criando uma janela
	  window = nullptr;
	  window = SDL_CreateWindow("METAL GEAR LITE",
	      SDL_WINDOWPOS_UNDEFINED,
	      SDL_WINDOWPOS_UNDEFINED,
	      SCREEN_WIDTH,
	      SCREEN_HEIGHT,
	      SDL_WINDOW_SHOWN);
	  if (window==nullptr) { // Em caso de erro...
	    std::cout << SDL_GetError();
	    SDL_Quit();
	    throw 1;
	  }

	  // Inicializando o renderizador
	  renderer = SDL_CreateRenderer(
	      window, -1,
	      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	  if (renderer==nullptr) { // Em caso de erro...
	    SDL_DestroyWindow(window);
	    std::cout << SDL_GetError();
	    SDL_Quit();
	    throw 1;
	  }
  }
  catch(int i){std::cout << "SDL ERROR" <<std::endl;}

  
  // Load TileSheet
  bgTiles = IMG_LoadTexture(renderer, "../assets/72x72/72x72_tiles.png");
  doorTiles = IMG_LoadTexture(renderer, "../assets/custom/doorVert.png");
  playerSheet = IMG_LoadTexture(renderer, "../assets/mg2/snakeSprites.png");
  testTile = IMG_LoadTexture(renderer, "../assets/test/testPlayer.png");
  mainTitle = IMG_LoadTexture(renderer, "../assets/main.png");
  exclamationText = IMG_LoadTexture(renderer, "../assets/exclamation.png");
  heliportText = IMG_LoadTexture(renderer, "../assets/heliport.png");

  camera_cimaTile = IMG_LoadTexture(renderer, "../assets/camera2.0/cameraCima.png");
  camera_cima_direitaTile = IMG_LoadTexture(renderer, "../assets/camera2.0/cameraCimaDir.png");
  camera_cima_esquerdaTile = IMG_LoadTexture(renderer, "../assets/camera2.0/cameraCimaEsq.png");
  camera_baixoTile = IMG_LoadTexture(renderer, "../assets/camera2.0/cameraBaixo.png");
  camera_baixo_direitaTile = IMG_LoadTexture(renderer, "../assets/camera2.0/cameraBaixoDir.png");
  camera_baixo_esquerdaTile = IMG_LoadTexture(renderer, "../assets/camera2.0/cameraBaixoEsq.pngg");
  camera_direitaTile = IMG_LoadTexture(renderer, "../assets/camera2.0/cameraDireita.png");
  camera_esquerdaTile = IMG_LoadTexture(renderer, "../assets/camera2.0/cameraEsquerda.png");

  // Set clipping rectangles
  corridorRect.w = tileSize;
  corridorRect.h = tileSize;
  corridorRect2.w = tileSize;
  corridorRect2.h = tileSize;
  corridorRect3.w = tileSize;
  corridorRect3.h = tileSize;

  wallRect.w = tileSize;
  wallRect.h = tileSize;
  wallRect2.w = tileSize;
  wallRect2.h = tileSize;
  wallRect3.w = tileSize;
  wallRect3.h = tileSize;
  wallRect4.w = tileSize;
  wallRect4.h = tileSize;
  wallRect5.w = tileSize;
  wallRect5.h = tileSize;
  wallRect6.w = tileSize;
  wallRect6.h = tileSize;

  portaFechadaRect.w = tileSize;; 
  portaFechadaRect.h = tileSize;; 
  portaAbertaRect.w = tileSize;; 
  portaAbertaRect.h = tileSize;; 

  cameraCimaRect.w = tileSize;
  cameraCimaRect.h = tileSize;
  cameraCimaDirRect.w = tileSize;
  cameraCimaDirRect.h = tileSize;
  cameraCimaEsqRect.w = tileSize;
  cameraCimaEsqRect.h = tileSize;
  cameraBaixoRect.w = tileSize;
  cameraBaixoRect.h = tileSize;
  cameraBaixoDirRect.w = tileSize;
  cameraBaixoDirRect.h = tileSize;
  cameraBaixoEsqRect.w = tileSize;
  cameraBaixoEsqRect.h = tileSize;
  cameraEsqRect.w = tileSize;
  cameraEsqRect.h = tileSize;
  cameraDirRect.w = tileSize;
  cameraDirRect.h = tileSize;

  emptyRect.w = tileSize; 
  emptyRect.h = tileSize; 
  topU_Rect.w = tileSize; 
  topU_Rect.h = tileSize; 
  topUR_Rect.w = tileSize; 
  topUR_Rect.h = tileSize; 
  topR_Rect.w = tileSize; 
  topR_Rect.h = tileSize; 
  topDR_Rect.w = tileSize; 
  topDR_Rect.h = tileSize; 
  topD_Rect.w = tileSize; 
  topD_Rect.h = tileSize; 
  topDL_Rect.w = tileSize; 
  topDL_Rect.h = tileSize; 
  topL_Rect.w = tileSize; 
  topL_Rect.h = tileSize; 
  topUL_Rect.w = tileSize; 
  topUL_Rect.h = tileSize; 

  corridorRect.x = 0;
  corridorRect.y = 0;
  corridorRect2.x = 0;
  corridorRect2.y = 1*tileSize;
  corridorRect3.x = 2*tileSize;
  corridorRect3.y = 4*tileSize;

  wallRect.x = 1*tileSize;
  wallRect.y = 9*tileSize;
  wallRect2.x = 2*tileSize;
  wallRect2.y = 9*tileSize;
  wallRect3.x = 1*tileSize;
  wallRect3.y = 14*tileSize;
  wallRect4.x = 1*tileSize;
  wallRect4.y = 15*tileSize;
  wallRect5.x = 2*tileSize;
  wallRect5.y = 14*tileSize;
  wallRect6.x = 2*tileSize;
  wallRect6.y = 15*tileSize;

  portaFechadaRect.x = 0;
  portaFechadaRect.y = 1*tileSize; 
  portaAbertaRect.x = 0;
  portaAbertaRect.y = 0;

  emptyRect.x = 2*tileSize; 
  emptyRect.y = 7*tileSize; 
  topU_Rect.x = 2*tileSize; 
  topU_Rect.y = 6*tileSize; 
  topUR_Rect.x = 3*tileSize; 
  topUR_Rect.y = 6*tileSize; 
  topR_Rect.x = 3*tileSize; 
  topR_Rect.y = 7*tileSize; 
  topDR_Rect.x = 3*tileSize; 
  topDR_Rect.y = 8*tileSize; 
  topD_Rect.x = 2*tileSize; 
  topD_Rect.y = 8*tileSize; 
  topDL_Rect.x = 1*tileSize; 
  topDL_Rect.y = 8*tileSize; 
  topL_Rect.x = 1*tileSize; 
  topL_Rect.y = 7*tileSize; 
  topUL_Rect.x = 1*tileSize; 
  topUL_Rect.y = 6*tileSize; 

  // Populate Player Frame Rectangles
  for (int i=0; i<12; i++){
  	playerSprites.push_back(new SDL_Rect);
	playerSprites.back()->w = 24;
	playerSprites.back()->h = 42-10;
	playerSprites.back()->x = i*24;
	playerSprites.back()->y = 5;
  }

  // Set target rectangle
  tileRect.w = tileSize;
  tileRect.h = tileSize;

  // Populate the Texture Dictionary
  // Map Tileset (name) -> (tilesheet, src_rect)
  textDict.insert(std::make_pair("wall", std::make_tuple(bgTiles, &wallRect, 0)));
  textDict.insert(std::make_pair("corridor", std::make_tuple(bgTiles, &corridorRect, 0)));
  textDict.insert(std::make_pair("start", std::make_tuple(bgTiles, &corridorRect, 0)));
  textDict.insert(std::make_pair("end", std::make_tuple(heliportText, nullptr, 1)));

  textDict.insert(std::make_pair("porta_fechada", std::make_tuple(doorTiles, &portaFechadaRect, 1)));
  textDict.insert(std::make_pair("porta_aberta", std::make_tuple(doorTiles, &portaAbertaRect, 1)));

  textDict.insert(std::make_pair("camera_cima", std::make_tuple(camera_cimaTile, nullptr, 1)));
  textDict.insert(std::make_pair("camera_cima_direita", std::make_tuple(camera_cima_direitaTile, nullptr, 1)));
  textDict.insert(std::make_pair("camera_cima_esquerda", std::make_tuple(camera_cima_esquerdaTile, nullptr, 1)));
  textDict.insert(std::make_pair("camera_baixo", std::make_tuple(camera_baixoTile, nullptr, 1)));
  textDict.insert(std::make_pair("camera_baixo_direita", std::make_tuple(camera_baixo_direitaTile, nullptr, 1)));
  textDict.insert(std::make_pair("camera_baixo_esquerda", std::make_tuple(camera_baixo_esquerdaTile, nullptr, 1)));
  textDict.insert(std::make_pair("camera_direita", std::make_tuple(camera_direitaTile, nullptr, 1)));
  textDict.insert(std::make_pair("camera_esquerda", std::make_tuple(camera_esquerdaTile, nullptr, 1)));

  textDict.insert(std::make_pair("empty", std::make_tuple(bgTiles, &emptyRect, 0)));
  textDict.insert(std::make_pair("topU", std::make_tuple(bgTiles, &topU_Rect, 0)));
  textDict.insert(std::make_pair("topUR", std::make_tuple(bgTiles, &topUR_Rect, 0)));
  textDict.insert(std::make_pair("topR", std::make_tuple(bgTiles, &topR_Rect, 0)));
  textDict.insert(std::make_pair("topDR", std::make_tuple(bgTiles, &topDR_Rect, 0)));
  textDict.insert(std::make_pair("topD", std::make_tuple(bgTiles, &topD_Rect, 0)));
  textDict.insert(std::make_pair("topDL", std::make_tuple(bgTiles, &topDL_Rect, 0)));
  textDict.insert(std::make_pair("topL", std::make_tuple(bgTiles, &topL_Rect, 0)));
  textDict.insert(std::make_pair("topUL", std::make_tuple(bgTiles, &topUL_Rect, 0)));

  textDict.insert(std::make_pair("to0", std::make_tuple(bgTiles, &corridorRect, 0)));
  textDict.insert(std::make_pair("to1", std::make_tuple(bgTiles, &corridorRect, 0)));
  textDict.insert(std::make_pair("to2", std::make_tuple(bgTiles, &corridorRect, 0)));
  textDict.insert(std::make_pair("to3", std::make_tuple(bgTiles, &corridorRect, 0)));

  // Load Player Texture
  textDict.insert(std::make_pair("player", std::make_tuple(playerSheet, nullptr, 0)));
}

/* Draws the scene */
void Viewer::render(std::map<int ,std::shared_ptr<Player>>& monitorPlayers, int currentMap){
	SDL_RenderClear(renderer);
	// Map Rendering
	std::map<std::pair<int, int>, std::string>::iterator it;
	// pseudo random int
	int random=0;
	for (it = textMap.begin(); it!=textMap.end(); ++it){
		// code coordinates
		tileRect.x = std::get<0>(it->first)*tileRect.w;
		tileRect.y = std::get<1>(it->first)*tileRect.w;
		// render texture inside tileRect
		// texture overlays: render on top of base texture
		if (std::get<2>(textDict[it->second])){
			SDL_RenderCopy(renderer, std::get<0>(textDict["corridor"]), &corridorRect, &tileRect);
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), std::get<1>(textDict[it->second]), &tileRect);
		}
		// randomly assign corridor texture
		else if (it->second=="corridor"){
		  random  = std::round(corrDistr(generator));
		  if (corridorRects.find(it->first) == corridorRects.end()){
			  if (random==1)
				  corridorRects.insert(std::make_pair(it->first, 1));
			  else if (random==2)
				  corridorRects.insert(std::make_pair(it->first, 2));
			  else if (random==3)
				  corridorRects.insert(std::make_pair(it->first, 3));
			  else 
				  corridorRects.insert(std::make_pair(it->first, 1));
		  //std::cout << corridorRects[it->first]<< std::endl; 
		  }
		  if (corridorRects[it->first]==1)
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), &corridorRect, &tileRect);
		  else if (corridorRects[it->first]==2)
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), &corridorRect2, &tileRect);
		  else if (corridorRects[it->first]==3)
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), &corridorRect3, &tileRect);
		}
		// randomly assign wall texture
		else if (it->second=="wall"){
		  random  = std::round(wallDist(generator));
		  if (wallRects.find(it->first) == wallRects.end()){
			  if (random==1)
				  wallRects.insert(std::make_pair(it->first, 1));
			  else if (random==2)
				  wallRects.insert(std::make_pair(it->first, 2));
			  else if (random==3)
				  wallRects.insert(std::make_pair(it->first, 3));
			  else if (random==4)
				  wallRects.insert(std::make_pair(it->first, 4));
			  else if (random==5)
				  wallRects.insert(std::make_pair(it->first, 5));
			  else if (random==6)
				  wallRects.insert(std::make_pair(it->first, 6));
			  else
				  wallRects.insert(std::make_pair(it->first, 4));
		  }
		  if (wallRects[it->first]==1)
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), &wallRect, &tileRect);
		  else if (wallRects[it->first]==2)
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), &wallRect2, &tileRect);
		  else if (wallRects[it->first]==3)
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), &wallRect3, &tileRect);
		  else if (wallRects[it->first]==4)
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), &wallRect4, &tileRect);
		  else if (wallRects[it->first]==5)
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), &wallRect5, &tileRect);
		  else if (wallRects[it->first]==6)
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), &wallRect6, &tileRect);
		}
		// base textures
		else
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), std::get<1>(textDict[it->second]), &tileRect);
	}
	// Player Rendering
	// make sure the texture is rendered above the bounding box
	std::map<int, std::shared_ptr<Player>>::iterator pl;
	SDL_Rect playerRect;
	for (pl = monitorPlayers.begin(); pl != monitorPlayers.end(); pl++){
		// only render players in the client current map
		if (pl->second->getCurrentMap() == currentMap){
			playerRect.x = pl->second->getX();
			playerRect.y = pl->second->getY();
			playerRect.w = pl->second->getW();
			playerRect.h = pl->second->getH();
			SDL_RenderCopy(renderer, std::get<0>(textDict["player"]), playerSprites[pl->second->getFrame()], &playerRect);
		}
	}
	SDL_RenderPresent(renderer);
	return;
}

void Viewer::updateMap(std::map<std::pair<int, int>, std::string>& textMap){
	this->textMap = textMap;
}

Viewer::~Viewer(){
	std::map<std::string, std::tuple<SDL_Texture*, SDL_Rect*, int>>::iterator it;
	for (it = textDict.begin(); it!=textDict.end(); ++it){
		SDL_DestroyTexture(std::get<0>(textDict[it->first]));
	}

  	for (int i=0; i<12; i++){
		delete playerSprites[i];
	}

	SDL_DestroyTexture(bgTiles);
	SDL_DestroyTexture(doorTiles);
	SDL_DestroyTexture(testTile);
	SDL_DestroyTexture(playerSheet);
	SDL_DestroyTexture(heliportText);

 	SDL_DestroyTexture(camera_cimaTile);
 	SDL_DestroyTexture(camera_cima_direitaTile);
 	SDL_DestroyTexture(camera_cima_esquerdaTile);
 	SDL_DestroyTexture(camera_baixoTile);
 	SDL_DestroyTexture(camera_baixo_direitaTile);
 	SDL_DestroyTexture(camera_baixo_esquerdaTile);
 	SDL_DestroyTexture(camera_direitaTile);
 	SDL_DestroyTexture(camera_esquerdaTile);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Viewer::renderMain(){
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, mainTitle, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

void Viewer::renderExclamation(Camera& cam){
  cam.setTextSize(50,75);
  SDL_Rect camRect;
  camRect.x = cam.getX();
  camRect.y = cam.getY();
  camRect.w = cam.getW();
  camRect.h = cam.getH();
  SDL_RenderCopy(renderer, exclamationText, nullptr, &camRect);
  SDL_RenderPresent(renderer);
  SDL_Delay(1000);
}
