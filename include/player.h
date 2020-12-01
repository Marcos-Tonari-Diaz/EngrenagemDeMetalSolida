#ifndef PLAYER_H
#define PLAYER_H

#include "json.hpp"
#include "element.h"
#include <iostream>

using nlohmann::json;

 /*! \brief Classe Player
   *
   *  Herda de Elementos.
   *  Adiciona controle de frames (animação)
   *  
   */
class Player : public Element {
	public:
		/*! Frame atual */
		int frame = 0;
		/*! Contador para controle */
		int counter = 0;
		/*! \brief Construtor do Player
       	* Define posição.
       	* \param x coordenada x
       	* \param y coordenada y
     		*/
		Player(int x, int y);
		/*! \brief Macro para json.
		*
		*/
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Player, x, y, w, h, frame, counter);
		int getFrame();	
		void setFrame(std::string s);	
};

#endif
