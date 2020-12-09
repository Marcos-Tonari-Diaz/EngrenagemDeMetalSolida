#ifndef TR_H
#define TR_H

#include "json.hpp"
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

/*! \brief Classe para enviar dados.
*	Essa classe passa dados aos clientes do servidor por arquivos json.
*
*  A calsse possuí uma função, send (enviar).
*/
class TRcontroller{
	public:
		/*! \brief Inicializador do objeto "Transference Controller".
		 *		
		 *
		 *  O inicializador do objeto é padrão.
		 */
		TRcontroller() = default;
		/*! \brief Função que envia o estado atual do jogo para os clientes do servidor.
		 *	
		 * \param j Arquivo json com o estado atual do jogo.
		 * \param IP Endereço de ip do servidor do jogo.
		 */
		void sendState(nlohmann::json j, int porta);
		nlohmann::json receiveState();
};

#endif
