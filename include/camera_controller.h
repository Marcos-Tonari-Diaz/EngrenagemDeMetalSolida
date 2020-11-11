#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H
#include "camera.h"
#include "player.h"
#include "map.h"
#include <stdio.h>
#include <memory>
#include <iostream>


/*! \brief Classe controller do objeto camera".
*
*
*  Classe com variáveis internas e funções de controle da camera.
*/
class Camera_controller {
	private:
		int tile_size = 72; /*!< tile_size (tamanho do tile do mapa) */
		int boundBoxSize = 0; /*!< boundBox (tamanho da caixa de colisão do jogador) */
	public:
		 /*! \brief Inicializador do objeto "Camera Controller".
		 *		
		 *
		 *  O inicializador do objeto é padrão.
		 */
		Camera_controller() = default;
		 /*! \brief Função de checagem de campo de visão.
		 *		Checa se o player está no campo de visão da camera.
		 *
		 * \param mapa Mapa do jogo
		 * \param camera Camera que se quer verificar
		 * \param jogador Jogador em questão
		 */
		void visao(Map& mapa, Camera& camera, Player& jogador);
		/*! \brief Função de checagem da validade do avistamento.
		 *		Checa se há obstaculos entre o jogador e a camera.
		 *
		 * \param mapa Mapa do jogo
		 * \param camera Camera que se quer verificar
		 * \param jogador Jogador em questão
		 */
		void deteccao(Map& mapa, Camera& camera, Player& jogador);
		/*! \brief Seta o valor de BoundSize.
		 *		Esse valor dita o tamanho da caixa de colisão do jogador.
		 *
		 *  \param s Valor novo do BoundSize.
		 */
		void setBoundBoxSize(int s);
		/*! \brief Seta o valor do TileSize.
		 *		Esse valor dita o tamanho do tile do mapa usado.
		 *
		 *  \param s Valor novo do tileSize.
		 */
		void setTileSize(int s);
};

#endif