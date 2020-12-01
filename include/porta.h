#ifndef PORTA_H
#define PORTA_H

#include "element.h"
#include "json.hpp"
#include "map.h"

using nlohmann::json;

/*! \brief Classe para o objeto Porta.
*	Essa classe herda da classe Element.
*
*  A porta tem o funcionamento simples de abrir e fechar, tendo uma flag interna para guardar seu estado.
*/
class Porta : public Element{
	private:
		int flag; /*!< flag (estado da porta 'aberta/fechada') */
	public:
		/*! \brief Inicializador do objeto "Porta".
		 *		
		 *
		 * \param x Coordenada x da porta
		 * \param y Coordenada y da porta
		 * \param flag Flag de estado da porta
		 */
		Porta(int x, int y, int flag);
		/*! \brief Macro para json.
		*
		*/
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Porta, flag);
		/*! \brief Função que atualiza o estado da porta.
		 *
		 */
		void atualiza_porta(int** collisionMap, int tile_size, Map& mapa);
		/*! \brief Função que retorna o estado da porta.
		 *		
		 */
		int get_flag();
		/*! \brief Função que seta o estado da porta.
		 *		
		 * \param flag Estado da porta
		 */
		void set_flag(int flag);
};

#endif
