#include <stdio.h>
#include <memory>
#include <iostream>
#include <vector>
#include "eventos.h"
#include "player.h"
#include "camera.h"

int Eventos::checagem(Player& player) {
	int delta_x; 
	int delta_y;
	int pH = player.getH();
	int pW = player.getW();
	// evento de mudanca de mapa (next)
	// retorna 0-3
	for (auto p: nextVec){
		// if player is on the same map as the portal
		if (player.getCurrentMap()==p.second.first){
			delta_x = fabs((p.first.first + tilesize/2) - (player.getX() + pW/2));
			delta_y = fabs((p.first.second + tilesize/2) - (player.getY() + pH/2));
			// player changes map
			if(delta_x <= tilesize/2 && delta_y <= tilesize/2){
				// update player 
				player.setCurrentMap(p.second.second);
				player.setPosition(startMap[player.getCurrentMap()]);
				// return map index
				return p.second.second;	
			}
		}
	}	
	// evento de tile final
	// retorna 4
	// if player is on the same map as the endTile
	if (player.getCurrentMap()==endMap){
		delta_x = fabs((x_final + tilesize/2) - (player.getX() + pW/2));
		delta_y = fabs((y_final + tilesize/2) - (player.getY() + pH/2));
		if(delta_x <= tilesize/2 && delta_y <= tilesize/2) {
			return 4;
		}
	}
	return 6;
}

int Eventos::checagem(Player& player, Camera& camera) {
	// evento de detecao da camera
	// retorna 5
	// if player is on the same map as camera
	if (player.getCurrentMap()==camera.getCurrentMap()){
		if(camera.get_detectado() == 1) 
			return 5;
	}
	return 6;
}

void Eventos::setEnd(int x, int y, int onMap){
	x_final = x;
	y_final = y;
	endMap = onMap;
}

void Eventos::setStart(int x, int y, int onMap){
	startMap.emplace(onMap, std::make_pair(x, y));
}

void Eventos::setNext(int x, int y, int onMap, int toMap){
	nextVec.emplace_back(std::make_pair(std::make_pair(x, y), std::make_pair(onMap, toMap)));
}
