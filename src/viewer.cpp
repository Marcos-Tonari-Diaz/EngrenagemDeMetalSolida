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
  
  // Carregando texturas
  // Map Tileset (name) -> (texture)
  textDict.insert(std::make_pair("wall", IMG_LoadTexture(renderer, "../assets/maps/test/test0.png")));
  textDict.insert(std::make_pair("corridor", IMG_LoadTexture(renderer, "../assets/maps/test/test0.png")));
  // update tile size
  SDL_QueryTexture(textDict["wall"], nullptr, nullptr, &tileSize, nullptr);

}

void Viewer::render(){
	// Desenhar a cena
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	return;
}

void Viewer::renderMap(std::map<std::pair<int, int>, std::string> textMap){
	SDL_RenderClear(renderer);

	SDL_Rect tileRect;
		
	tileRect.w = tileSize;
	tileRect.h = tileSize;

	// iterates the map
	int x;
	int y;
	std::map<std::pair<int, int>, std::string>::iterator it;
	for (it = textMap.begin(); it!=textMap.end(); ++it){
		// code coordinates
		x = std::get<0>(it->first);
		y = std::get<1>(it->first);
		tileRect.x = x*tileSize;
		tileRect.y = y*tileSize;
		// render texture inside tileRect
		SDL_RenderCopy(renderer, textDict[it->second], nullptr, &tileRect);
	}
	SDL_RenderPresent(renderer);
}

Viewer::~Viewer(){
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = textDict.begin(); it!=textDict.end(); ++it){
		SDL_DestroyTexture(textDict[it->first]);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
