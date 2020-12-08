#include "sl_controller.h"
#include <fstream>
#include <iostream>
#include <string>
#include "porta.h"
#include "camera.h"
#include "player.h"

using nlohmann::json;

void SLcontroller::save() {
	std::ofstream f;
  	f.open("../assets/file.json", std::ofstream::out | std::ofstream::trunc);
  	f << this->file;
  	f.close();
}

void SLcontroller::add(Element& s, std::string tag) {
	if(tag[0] == 'p') {
		Porta& d = static_cast<Porta&>(s);
		this->file[tag] = d;
	}
	else if(tag[0] == 'c') {
		Camera& d = static_cast<Camera&>(s);
		this->file[tag] = d;
	}
	else if(tag[0] == 'y') {
		Player& d = static_cast<Player&>(s);
		this->file[tag] = d;
	}
}

void SLcontroller::clear() {
	json j;
	this->file = j;
}

void SLcontroller::load(Element& s, std::string tag) {
	json j;
	json aux;
	std::ifstream f;
  	f.open("../assets/file.json");
	if ((f.rdstate() & std::ifstream::failbit ) != 0 ){
    		std::cerr << "Error opening JSON state\n";
		return;
	}
  	f >> j;
  	f.close();
	if(tag[0] == 'p') {
		Porta& d = static_cast<Porta&>(s);
		aux = j[tag];
		d.set_flag(aux["flag"]);
		d.setCurrentMap(aux["currentMap"]);
	}
	else if(tag[0] == 'c') {
		Camera& d = static_cast<Camera&>(s);
		aux = j[tag];
		d.set_avistado(aux["avistado"]);
		d.set_detectado(aux["detectado"]);
		d.setCurrentMap(aux["currentMap"]);
	}
	else if(tag[0] == 'y') {
		Player& d = static_cast<Player&>(s);
		aux = j[tag];
		d.setPosition(aux["x"], aux["y"]);
		d.setFrame((int) aux["frame"]);
		d.setCounter(aux["counter"]);
		d.setCurrentMap(aux["currentMap"]);
	}
}
