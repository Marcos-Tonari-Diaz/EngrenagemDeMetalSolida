#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Model {
	public:
		const float m = 0.5;
		const float b = 0.2;
		const float k = 0.6;

		float x;
	       	float v;
		float outsideForce=0;
		
		Model(float x, float y);
};

Model::Model(float x, float v){
	this->x=x;	
	this->v=v;	
}

class screenPoint{
	public:
		int x;
		int y;
};

class Viewer{
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;

		// texturas
		SDL_Texture *texture;
		SDL_Texture *texture2;
		SDL_Rect target;
		
		// Controlador:
		bool rodando = true;

		// Variaveis para verificar eventos
		SDL_Event evento; // eventos discretos

		const int SCREEN_WIDTH = 400;
		const int SCREEN_HEIGHT = 400;

		const Uint8* state = SDL_GetKeyboardState(nullptr); // estado do teclado
		void render();
		int initSDL();
		void destroyAll();
		
};

int Viewer::initSDL(){
  // Inicializando o subsistema de video do SDL
  if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
    std::cout << SDL_GetError();
    return 1;
  }

  // Criando uma janela
  window = nullptr;
  window = SDL_CreateWindow("Demonstracao do SDL2",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_SHOWN);
  if (window==nullptr) { // Em caso de erro...
    std::cout << SDL_GetError();
    SDL_Quit();
    return 1;
  }

  // Inicializando o renderizador
  renderer = SDL_CreateRenderer(
      window, -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer==nullptr) { // Em caso de erro...
    SDL_DestroyWindow(window);
    std::cout << SDL_GetError();
    SDL_Quit();
    return 1;
  }

  // Carregando texturas
  // personagem
  texture = IMG_LoadTexture(renderer, "./capiSmall.png");

  // Quadrado onde a textura sera desenhada
  target.x = 0;
  target.y = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, &target.w, &target.h);
}

void Viewer::render(){
	// Desenhar a cena
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture2, nullptr, nullptr);
	SDL_RenderCopy(renderer, texture, nullptr, &target);
	SDL_RenderPresent(renderer);
	return;
}

void Viewer::destroyAll(){
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//contas
class IterFisica {
	private:
		// intervalo de tempo
		const float T = 0.3;	
	public:
		// Metodo de Euler 
		// Retorna a velocidade da iteracao
		void iter(std::shared_ptr<Model> box);
};

void IterFisica::iter(std::shared_ptr<Model> box){
	//previos
	float Pv = box->v;
	float Px = box->x;

	box->x = Px + T*Pv;
	box->v = Pv + T*(-1/box->m)*(box->b*Pv + box->k*Px + box->outsideForce);
	return;
}

//coordinates e SDL
class Window {
	private:
		//screen 
		const int height=400;
		const int width=200;
	public:
		// Rasterizacao
		void coordinates(std::shared_ptr<screenPoint> point, std::shared_ptr<Model> aBox);
};

void Window::coordinates(std::shared_ptr<screenPoint> point, std::shared_ptr<Model> aBox){
	int x_trunc = (int) aBox->x;

	if (aBox->x-x_trunc<0.5){
		aBox->x = x_trunc;
	}
	else{
		aBox->x = x_trunc++;
	}
	point->x = width/2;
	point->y = height/2-4*(aBox->x);

	//std::cout << point->x << ", " << point->y << std::endl;
	return ;
}

class Controller {
	private:
		std::shared_ptr<Model> const aBox;
		std::shared_ptr<Viewer> const aScreen;
		std::shared_ptr<IterFisica> const iterFis;
		std::shared_ptr<Window> const window;

	public:
		Controller(std::shared_ptr<Model> aBox, std::shared_ptr<Viewer> aScreen, std::shared_ptr<IterFisica> iterFis, std::shared_ptr<Window> window);
		// Metodo de Euler 
		// Retorna a velocidade da iteracao
		void simulate();
		void eventPolling();
};

Controller::Controller(std::shared_ptr<Model> aBox, std::shared_ptr<Viewer> aScreen, std::shared_ptr<IterFisica> iterFis, std::shared_ptr<Window> window): aBox(aBox), aScreen(aScreen), iterFis(iterFis), window(window){
}

void Controller::eventPolling(){
	// Polling de eventos
	SDL_PumpEvents(); // atualiza estado do teclado
	// forca externa
	if (aScreen->state[SDL_SCANCODE_UP]) aBox->outsideForce -= 1;
	else if (aScreen->state[SDL_SCANCODE_DOWN]) aBox->outsideForce += 1;
	else aBox->outsideForce = 0;
}

void Controller::simulate(){
	//ponto2D
	std::shared_ptr<screenPoint> point(new screenPoint); 

	aScreen->initSDL();

	int resetCounter = 0;

	// Laco principal do jogo
	while(aScreen->rodando) {
		
		eventPolling();

		//fisica
		iterFis->iter(aBox);
		
		// reset outside force
		resetCounter++;
		if (resetCounter>25){
		       	aBox->outsideForce = 0;
			resetCounter=0;
		}

		//rasterizacao
		window->coordinates(point, aBox);
		aScreen->target.x = point->x;
		aScreen->target.y = point->y;

		while (SDL_PollEvent(&(aScreen->evento))) {
			if (aScreen->evento.type == SDL_QUIT) {
				aScreen->rodando = false;
			}
		}

		aScreen->render();

		// Delay para diminuir o framerate
		SDL_Delay(35);
	}
	aScreen->destroyAll();

	/*
	for (int i=0; i < n_iter; i++){
		iterFis->iter(box);
		window->coordinates(point, box);
	}
	*/
}

int main(){
	std::shared_ptr<Model> aBox (new Model(0.0, 75.0));
	std::shared_ptr<Viewer> aScreen (new Viewer);
	std::shared_ptr<IterFisica> iterFis (new IterFisica);
	std::shared_ptr<Window> window (new Window);
	Controller controller(aBox, aScreen, iterFis, window);
	controller.simulate();
	return 0;
}
