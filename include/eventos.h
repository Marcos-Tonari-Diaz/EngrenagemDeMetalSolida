#ifndef EVENTOS_H
#define EVENTOS_H
#include <stdio.h>
#include <memory>
#include <iostream>
#include <vector>
#include "player.h"
#include "camera.h"
#include <math.h>

class Eventos {
	private:
	    /*! Coordenada do fim da fase */
		int x_final = 72*9;
		/*! Coordenada do fim da fase */
		int y_final = 72*9;
		/*! Coordenada do inicio da fase */
		int x_inicial = 0;
		/*! Coordenada do inicio da fase */
		int y_inicial = 0;
	public:
		/*! \brief Checagem de camera e fim de fase
     	*  Checar se alguma camera detectou o jogador ou se o jogador chegou no fim da fase.
		* \param jogador Jogador
		* \param camera Camera
		* \param tilesize Tamanho da textura
		* \param boundingbox Bounding box do jogador
     	* */
		int checagem(Player& jogador, Camera& camera, int tilesize, int boundingbox);
		void setEnd(int x, int y);
};

#endif
