#ifndef PORTA_CONTROLLER_H
#define PORTA_CONTROLLER_H
#include <iostream>
#include <memory>
#include <cmath>
#include "player.h"
#include "porta.h"
#include "map.h"

/*! \brief Classe controller do objeto "Porta".
*
*
*  Classe com variáveis internas e funções de controle da porta.
*/
class Porta_controller {
	private:
		int tile_size = 0; /*!< tile_size (tamanho do tile do mapa) */
		int boundBoxSize = 0; /*!< boundBox (tamanho da caixa de colisão do jogador) */
	public:
		/*! \brief Inicializador do objeto "Camera Controller".
		 *		
		 *
		 *  O inicializador do objeto é padrão.
		 */
		Porta_controller() = default;
		/*! \brief Função de mudança de estado da porta.
		 *		Abre a porta caso ela esteja fechada e fecha a porta caso ela esteja aberta.
		 *
		 * \param porta Porta a ser analisada
		 * \param jogador Jogador em questão
		 * \param mapa Mapa do jogo
		 * \param state Variável do estado do teclado
		 * \param collisionMap Mapa de colisão do "mapa e jogador"
		 */
		void abre_fecha(Porta& porta, Player& jogador, Map& mapa, const Uint8* state, int** collisionMap);
		/*! \brief Seta o valor do TileSize.
		 *		Esse valor dita o tamanho do tile do mapa usado.
		 *
		 *  \param s Valor novo do tileSize.
		 */
		void setTileSize(int s);
		/*! \brief Seta o valor de BoundSize.
		 *		Esse valor dita o tamanho da caixa de colisão do jogador.
		 *
		 *  \param s Valor novo do BoundSize.
		 */
		void setBoundBoxSize(int s);
};

#endif