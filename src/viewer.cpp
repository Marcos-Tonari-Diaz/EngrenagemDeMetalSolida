#include "viewer.h"

Viewer::Viewer(){
  // Inicializando o subsistema de video do SDL
  try{
	  if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
	    std::cout << SDL_GetError();
	    throw 1;
	  }

	  // Criando uma janela
	  window = nullptr;
	  window = SDL_CreateWindow("ENGRENAGEM DE METAL SOLIDA",
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

  // Set clipping rectangles
  corridorRect.w = tileSize;
  corridorRect.h = tileSize;
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
  textDict.insert(std::make_pair("wall", std::make_pair(bgTiles, &wallRect)));
  textDict.insert(std::make_pair("corridor", std::make_pair(bgTiles, &corridorRect)));

  textDict.insert(std::make_pair("porta_fechada", std::make_pair(doorTiles, &portaFechadaRect)));
  textDict.insert(std::make_pair("porta_aberta", std::make_pair(doorTiles, &portaAbertaRect)));

  textDict.insert(std::make_pair("camera_cima", std::make_pair(testTile, nullptr)));
  textDict.insert(std::make_pair("camera_cima_direita", std::make_pair(testTile, nullptr)));
  textDict.insert(std::make_pair("camera_cima_esquerda", std::make_pair(testTile, nullptr)));
  textDict.insert(std::make_pair("camera_baixo", std::make_pair(testTile, &wallRect)));
  textDict.insert(std::make_pair("camera_baixo_direita", std::make_pair(testTile, nullptr)));
  textDict.insert(std::make_pair("camera_baixo_esquerda", std::make_pair(testTile, nullptr)));
  textDict.insert(std::make_pair("camera_direita", std::make_pair(testTile, nullptr)));
  textDict.insert(std::make_pair("camera_esquerda", std::make_pair(testTile, nullptr)));

  // Load Player Texture
  textDict.insert(std::make_pair("player", std::make_pair(playerSheet, nullptr)));


  //debbug
  //textDict.insert(std::make_pair("player", std::make_pair(IMG_LoadTexture(renderer, "../assets/test/testPlayer.png"), nullptr)));
	

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
		if (it->second == "porta_aberta" || it->second == "porta_fechada"){
			SDL_RenderCopy(renderer, std::get<0>(textDict["corridor"]), &corridorRect, &tileRect);
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), std::get<1>(textDict[it->second]), &tileRect);
		}
		// base textures
		else
			SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), std::get<1>(textDict[it->second]), &tileRect);
  		//std::cout <<  it->second<< std::endl;
	}
	// Player
	// make sure the texture is rendered above the bounding box
	SDL_RenderCopy(renderer, std::get<0>(textDict["player"]), playerSprites[player.getFrame()], (player.getRect()));
	//player.incrementFrame();
	// debbug
	//SDL_RenderCopy(renderer, std::get<0>(textDict["player"]), nullptr, (player.getRect()));
	/*
  SDL_Rect test;
  test.x = 3*72;
  test.y = 3*72;
  test.w = 72;
  test.h = 72;
  SDL_RenderCopy(renderer, doorTiles, nullptr, &test);
  */
	SDL_RenderPresent(renderer);
	return;
}

void Viewer::updateMap(std::map<std::pair<int, int>, std::string>& textMap){
	this->textMap = textMap;
}

Viewer::~Viewer(){
	std::map<std::string, std::pair<SDL_Texture*, SDL_Rect*>>::iterator it;
	for (it = textDict.begin(); it!=textDict.end(); ++it){
		SDL_DestroyTexture(std::get<0>(textDict[it->first]));
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
