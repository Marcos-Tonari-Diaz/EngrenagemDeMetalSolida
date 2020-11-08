#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <map>
#include <iostream>
#include "element.h"
#include "map.h"

class collisionController{
	private:
  		const Uint8* state = NULL;
		int boundBoxWidth = 0;
		int boundBoxHeight = 0;
		int** collisionMap = NULL;
		/*how many steps an element can move inside a tile*/
		int subdivision = 10;
		std::shared_ptr<Map> map;
	public:
		~collisionController();
		void makeCollisionMap();
		int acessCollisionMap(int x, int y);
		void move(Element& obj);
		int get_boundBoxWidth();
		int get_boundBoxHeight();
		void set_boundBoxWidth(int w);
		void set_boundBoxHeight(int h);
		void set_state(const Uint8* state);
		void set_map(std::shared_ptr<Map> map);
};

#endif
