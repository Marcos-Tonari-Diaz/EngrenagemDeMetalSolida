#include "collisionController.h"

void collisionController::playerEvents(){
	// Event Polling
	SDL_PumpEvents(); // Updates Keyboard State
	// updates player position
	if (state[SDL_SCANCODE_LEFT]) player->get_position().x -= step;
	if (state[SDL_SCANCODE_RIGHT]) player->get_position().x += step;
	if (state[SDL_SCANCODE_UP]) player->get_position().y -= step;
	if (state[SDL_SCANCODE_DOWN]) player->get_position().y += step;
}
