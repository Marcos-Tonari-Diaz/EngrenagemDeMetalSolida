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

  // Set clipping rectangles
  corridorRect.x = 0;
  corridorRect.y = 0;
  corridorRect.w = tileSize;
  corridorRect.h = tileSize;
  wallRect.x = 1*tileSize;
  wallRect.y = 9*tileSize;
  wallRect.w = tileSize;
  wallRect.h = tileSize;

  // Set target rectablge
  tileRect.w = tileSize;
  tileRect.h = tileSize;

  // Populate the Texture Dictionary
  // Map Tileset (name) -> (tilesheet, src_rect)
  textDict.insert(std::make_pair("corridor", std::make_pair(bgTiles, &corridorRect)));
  textDict.insert(std::make_pair("wall", std::make_pair(bgTiles, &wallRect)));
  
  // Populate Player Frame Rectangles
  for (int i=0; i<12; i++){
  	playerSprites.push_back(new SDL_Rect);
	playerSprites.back()->w = 24;
	playerSprites.back()->h = 42-10;
	playerSprites.back()->x = i*24;
	playerSprites.back()->y = 5;
  }
  // Load Player Texture
  textDict.insert(std::make_pair("player", std::make_pair(IMG_LoadTexture(renderer, "../assets/mg2/snakeSprites.png"), nullptr)));
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
		SDL_RenderCopy(renderer, std::get<0>(textDict[it->second]), std::get<1>(textDict[it->second]), &tileRect);
  		//std::cout <<  it->second<< std::endl;
	}
	// Player
	// make sure the texture is rendered above the bounding box
	SDL_RenderCopy(renderer, std::get<0>(textDict["player"]), playerSprites[player.getFrame()], (player.getRect()));
	//SDL_RenderCopy(renderer, std::get<0>(textDict["player"]), nullptr, (player.getRect()));
	//player.incrementFrame();
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
