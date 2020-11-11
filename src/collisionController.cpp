#include "collisionController.h"

void collisionController::makeCollisionMap(){
	// protection
	if (map->getHeight()==0 && map->getWidth()==0) return;
	// allocate collisionmap[y][x]
	collisionMap = new int*[map->getHeight()];
	for (int i=0; i < map->getHeight(); i++){
		collisionMap[i] = new int[map->getWidth()];
	// populate collisionmap
	}
	for (int i=0; i < map->getHeight(); i++){
		for(int j=0; j < map->getWidth(); j++){
			if(map->get_textMap()[std::make_pair(j,i)]=="corridor"
			  || map->get_textMap()[std::make_pair(j,i)]=="porta_aberta"
			){
				collisionMap[i][j] = 1;		
			}
			else{
				collisionMap[i][j] = 0;
			}
		}
	}
}

void collisionController::move(Player& obj){
	// polls offset
	int offsetX = 0;
	int offsetY = 0;
	if (state[SDL_SCANCODE_LEFT]){
		offsetX--; 
		obj.setFrame("left");
	}
	else if (state[SDL_SCANCODE_RIGHT]){
	       	offsetX++;
		obj.setFrame("right");
	}
	else if (state[SDL_SCANCODE_UP]){
	       	offsetY--; 
		obj.setFrame("up");
	}
	else if (state[SDL_SCANCODE_DOWN]){
	       	offsetY++;
		obj.setFrame("down");
	}
	else 
		obj.setFrame("iddle");


	// tests for map collision
	// updated coordinate: element coordinates are pixel coordinates (getX, getY)
	int x_mov = obj.getX()+offsetX*(boundBoxSize)/10;
	int y_mov = obj.getY()+offsetY*(boundBoxSize)/10;
	if ((x_mov < 0) || (y_mov < 0) ) return;
	// bounding box other corner (limit corner)
	int x_mov_lmt = x_mov + boundBoxSize;
	int y_mov_lmt = y_mov + boundBoxSize;
	if ((x_mov_lmt> (map->getWidth()*tileSize)) || (y_mov_lmt>(map->getHeight()*tileSize))) return;
		// if all corners are in free tiles, update element's position
		// obs: collisionMap is (y,x) (height, width)
		if(
		  ((collisionMap[(y_mov+2)/tileSize][(x_mov+2)/tileSize]==1)
		&& (collisionMap[(y_mov_lmt-2)/tileSize][(x_mov+2)/tileSize]==1)	
		&& (collisionMap[(y_mov_lmt-2)/tileSize][(x_mov_lmt-2)/tileSize]==1)	
		&& (collisionMap[(y_mov+2)/tileSize][(x_mov_lmt-2)/tileSize]==1))
		){
			obj.setPosition(x_mov, y_mov);	
		}
	// tests for element collision
}

collisionController::~collisionController(){
	//deallocate collision map
	if (collisionMap!= NULL){
		for (int i=0; i < map->getHeight(); i++){
			delete collisionMap[i];
		}
		delete collisionMap;
	}
}

void collisionController::set_boundBoxSize(int size){boundBoxSize = size;};
void collisionController::set_tileSize(int size){tileSize = size;};
void collisionController::set_state(const Uint8* state){this->state = state;}

void collisionController::set_map(std::shared_ptr<Map> map){
	this->map = map;
	makeCollisionMap();
}

int** collisionController::getCollisionMap(){return collisionMap;}
