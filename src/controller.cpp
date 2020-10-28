#include "controller.h"

Controller::Controller():viewer(new Viewer), map(new Map("../assets/maps/test.map")){
	
}

void Controller::gameLoop(){
	while(1){
		viewer->renderMap(map->get_textMap());	
	}		
}
