#ifndef EVENTOS_H
#define EVENTOS_H
#include <stdio.h>
#include <memory>
#include <iostream>
#include <vector>
#include "player.h"
#include "camera.h"
#include <math.h>


/*! \brief Classe para o objeto Eventos.
*	Objeto que realiza a checagem de eventos durante o jogo.
*
*  Classe com variáveis internas de localização e métodos de checagem e finalização do jogo.
*/
class Eventos {
	private:
		int x_final = 72*9; /*!< x_final (Coordenada x da posição alvo do jogador para o final do jogo) */
		int y_final = 72*9; /*!< y_final (Coordenada y da posição alvo do jogador para o final do jogo) */
		int x_inicial = 0; /*!< x_inicial (Coordenada x da posição inicial do jogador) */
		int y_inicial = 0; /*!< y_inicial (Coordenada y da posição inicial do jogador) */
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> nextVec;
		std::map<int, std::pair<int, int>> startMap;
		int tilesize;
		int endMap;
	public:
		/*! \brief Função que detecta a ocorrência de eventos.
		*	Eventos são ocorrências que exigem uma mudança no estado do jogo.
		*
		* \param jogador Jogador analisado em questão
		* \param cameras Vetor de todas as cameras presentes no mapa
		* \param tilesize Tamanho do tile usado no mapa
		* \param boundingbox Tamanho da caixa de colisão do jogador
		*/
		int checagem(Player& jogador, Camera& cameras);
		int checagem(Player& jogador);
		/*! \brief Função que inicializa as coordenadas finais do jogo.
		*
		* \param x Coordenada x final do mapa
		* \param y Coordenada y final do mapa
		*/
		void setEnd(int x, int y, int onMap);
		void setStart(int x, int y, int onMap);
		void setNext(int x, int y, int onMap, int toMap);
		void setTileSize(int size){tilesize = size;};
		//void reset(Player& jogador, std::vector<std::shared_ptr<Porta>>& portas, std::vector<std::shared_ptr<Camera>>& cameras, Map& mapa, int** collisionMap, Porta_controller& portacontroller);
};

#endif
