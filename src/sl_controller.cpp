#include "sl_controller.h"
#include <fstream>
#include <iostream>
#include <string>
#include "porta.h"
#include "camera.h"
#include "player.h"

using nlohmann::json;

void SLcontroller::save(std::string address) {
	std::ofstream f;
  	f.open(address, std::ofstream::out | std::ofstream::trunc);
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

json SLcontroller::get_file() {
	return (this->file);
}

void SLcontroller::load(Element& s, std::string tag, std::string address) {
	json j;
	json aux;
	std::ifstream f;
  	f.open(address);
  	f >> j;
  	f.close();
	if(tag[0] == 'p') {
		Porta& d = static_cast<Porta&>(s);
		aux = j[tag];
		d.set_flag(aux["flag"]);
	}
	else if(tag[0] == 'c') {
		Camera& d = static_cast<Camera&>(s);
		aux = j[tag];
		d.set_avistado(aux["avistado"]);
		d.set_detectado(aux["detectado"]);
	}
	else if(tag[0] == 'y') {
		Player& d = static_cast<Player&>(s);
		aux = j[tag];
		d.setPosition(aux["x"], aux["y"]);
	}
}
