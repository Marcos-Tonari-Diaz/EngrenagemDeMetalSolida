#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <map>
#include <iostream>
#include "player.h"
#include "map.h"

class collisionController{
	private:
  		const Uint8* state = NULL;
		int boundBoxSize = 0;
		int tileSize = 0;
		int** collisionMap = NULL;
		std::shared_ptr<Map> map;
	public:
		~collisionController();
		void makeCollisionMap();
		int acessCollisionMap(int x, int y);
		void move(Player& obj);
		void set_state(const Uint8* state);
		void set_map(std::shared_ptr<Map> map);
		void set_boundBoxSize(int size);
		void set_tileSize(int size);
		int** getCollisionMap();
};

#endif
