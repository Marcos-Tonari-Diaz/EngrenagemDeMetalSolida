#include <SDL2/SDL.h>

class collisionController{
	private:
  		const Uint8* state = SDL_GetKeyboardState(nullptr); // estado do teclado
	public:
		void playerEvents();
};
