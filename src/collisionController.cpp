#include "collisionController.h"

void collisionController::makeCollisionMap(){
	collisionMap = new int*[map->getHeight()];
	for (int i=0; i < map->getHeight(); i++){
		collisionMap[i] = new int[map->getWidth()];
	}
	for (int i=0; i < map->getHeight(); i++){
		for(int j=0; j < map->getWidth(); j++){
			if(map->get_textMap()[std::make_pair(j,i)]=="wall"){
				collisionMap[i][j] = 0;		
			}
			else{
				collisionMap[i][j] = 1;
			}
		}
	}
}

void collisionController::move(Element& obj){
	// polls offset
	int offsetX = 0;
	int offsetY = 0;
	if (state[SDL_SCANCODE_LEFT]) offsetX--; 
	if (state[SDL_SCANCODE_RIGHT]) offsetX++;
	if (state[SDL_SCANCODE_UP]) offsetY--; 
	if (state[SDL_SCANCODE_DOWN]) offsetY++;

	// tests for map collision
	// updated coordinate: element coordinates are pixel coordinates (getX, getY)
	int x_mov = obj.getX()+offsetX*(boundBoxSize);
	int y_mov = obj.getY()+offsetY*(boundBoxSize);
	if ((x_mov < 0) || (y_mov < 0) ) return;
	// bounding box other corner (limit corner)
	int x_mov_lmt = x_mov + boundBoxSize;
	int y_mov_lmt = y_mov + boundBoxSize;
	if ((x_mov_lmt> (map->getWidth()*boundBoxSize)) || (y_mov_lmt>(map->getHeight()*boundBoxSize))) return;
	std::cout << x_mov << ", " << y_mov << ", "<< x_mov_lmt << ", " << y_mov_lmt << std::endl;

	// if all corners are in free tiles, update element's position
	// obs: collisionMap is (y,x) (height, width)
	//if (x_mov >= 0 && y_mov >= 0 && x_mov_lmt < map->getWidth() && y_mov_lmt < map->getHeight()){
		if(
		  ((collisionMap[(y_mov+1)/boundBoxSize][(x_mov+1)/boundBoxSize]==1)
		&& (collisionMap[(y_mov_lmt-1)/boundBoxSize][(x_mov+1)/boundBoxSize]==1)	
		&& (collisionMap[(y_mov_lmt-1)/boundBoxSize][(x_mov_lmt-1)/boundBoxSize]==1)	
		&& (collisionMap[(y_mov+1)/boundBoxSize][(x_mov_lmt-1)/boundBoxSize]==1))
		){
			obj.setPosition(x_mov, y_mov);	
		}
	//}
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
void collisionController::set_state(const Uint8* state){this->state = state;}
void collisionController::set_map(std::shared_ptr<Map> map){this->map = map;}
