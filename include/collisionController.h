#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <map>
#include <iostream>
#include "player.h"
#include "map.h"

 /*! \brief Controle de Colisão
   *
   *  Controla movimentos e colisão.
   *  Atualiza o sprite da animação do jogador.
   *  
   */

class collisionController{
	private:
		/*! Estado do Teclado */
  		const Uint8* state = NULL;
		int boundBoxH = 0;
		int boundBoxW = 0;
		int tileSize = 0;
		/*! Mapa de colisão */
		int** collisionMap = NULL;
		/*! Ponteiro para mapa */
		std::shared_ptr<Map> map;
	public:
		/*! Desaloca mapa de colisão */
		~collisionController();
		/*! Gera mapa de colisão a partir do dicionário do mapa */
		void makeCollisionMap();
		/*! Move o player controlando a colisão
		 * \param obj Player a ser movido
		 * \param Up Codigo de tecla cima
		 * \param Down Codigo de tecla baixo
		 * \param left Codigo de tecla esquerda
		 * \param Right Codigo de tecla direita
		 */
		void move(Player& obj, int Up, int Down, int Left, int Right);
		void set_state(const Uint8* state);
		void set_map(std::shared_ptr<Map> map);
		void set_boundBoxSize(int w, int h);
		void set_tileSize(int size);
		int** getCollisionMap();
};

#endif
