#include "viewer.h"

Viewer::Viewer(): generator(2), corrDistr(0,1) {
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

  wallRect.w = tileSize;
  wallRect.h = tileSize;

  portaFechadaRect.w = tileSize;; 
  portaFechadaRect.h = tileSize;; 
  portaAbertaRect.w = tileSize;; 
  portaAbertaRect.h = tileSize;; 

  cameraCimaRect.w = tileSize;; 
  cameraCimaRect.h = tileSize;; 
  cameraCimaDirRect.w = tileSize;; 
  cameraCimaDirRect.h = tileSize;; 
  cameraCimaEsqRect.w = tileSize;; 
  cameraCimaEsqRect.h = tileSize;; 
  cameraBaixoRect.w = tileSize;; 
  cameraBaixoRect.h = tileSize;; 
  cameraBaixoDirRect.w = tileSize;; 
  cameraBaixoDirRect.h = tileSize;; 
  cameraBaixoEsqRect.w = tileSize;; 
  cameraBaixoEsqRect.h = tileSize;; 
  cameraEsqRect.w = tileSize;; 
  cameraEsqRect.h = tileSize;; 
  cameraDirRect.w = tileSize;; 
  cameraDirRect.h = tileSize;; 

  corridorRect.x = 0;
  corridorRect.y = 0;
  corridorRect2.x = 0;
  corridorRect2.y = 1*tileSize;
  wallRect.x = 1*tileSize;
  wallRect.y = 9*tileSize;
  portaFechadaRect.x = 0;; 
  portaFechadaRect.y = 1*tileSize;; 
  portaAbertaRect.x = 0;
  portaAbertaRect.y = 0;

  // Populate Player Frame Rectangles
  for (int i=0; i<12; i++){
  	playerSprites.push_back(new SDL_Rect);
	playerSprites.back()->w = 24;
	playerSprites.back()->h = 42-10;
	playerSprites.back()->x = i*24;
	playerSprites.back()->y = 5;
  }

  // Set target rectanglge
  tileRect.w = tileSize;
  tileRect.h = tileSize;

  // Populate the Texture Dictionary
  // Map Tileset (name) -> (tilesheet, src_rect)
  textDict.insert(std::make_pair("wall", std::make_tuple(bgTiles, &wallRect, 0)));
  textDict.insert(std::make_pair("corridor", std::make_tuple(bgTiles, &corridorRect, 0)));
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

  // Load Player Texture
  textDict.insert(std::make_pair("player", std::make_tuple(playerSheet, nullptr, 0)));
  

}

/* Draws the scene */
void Viewer::render(Player& player){
	SDL_RenderClear(renderer);
	// Map
	std::map<std::pair<int, int>, std::string>::iterator it;
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
		  if (corridorRects.find(it->first) == corridorRects.end()){
			  if (corrDistr(generator)==1)
				  corridorRects.insert(std::make_pair(it->first, 1));
			  else
				  corridorRects.insert(std::make_pair(it->first, 0));
		  //std::cout << corridorRects[it->first]<< std::endl; 
		  }
		  if (corridorRects[it->first]==0)
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), &corridorRect, &tileRect);
		  else
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), &corridorRect2, &tileRect);
		}
		// base textures
		else
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), std::get<1>(textDict[it->second]), &tileRect);
	}
	// Player
	// make sure the texture is rendered above the bounding box
        SDL_Rect playerRect;
	playerRect.x = player.getX();
	playerRect.y = player.getY();
	playerRect.w = player.getW();
	playerRect.h = player.getH();
	SDL_RenderCopy(renderer, std::get<0>(textDict["player"]), playerSprites[player.getFrame()], &playerRect);
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
