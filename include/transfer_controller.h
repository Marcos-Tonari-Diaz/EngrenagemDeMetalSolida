#ifndef TR_H
#define TR_H

#include "json.hpp"
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::udp;

/*! \brief Classe para enviar dados.
*	Essa classe passa dados aos clientes do servidor por arquivos json.
*
*  A calsse possuí uma função, send (enviar).
*/
class TRcontroller{
	private:
		std::vector<boost::asio::ip::udp::endpoint> remote_endpoints;
		std::vector<const char*> commands;
		int flag = 1;
	public:
		boost::asio::io_service my_io_service;
		udp::endpoint local_endpoint;
		udp::endpoint remote_endpoint;
		udp::socket my_socket;

		/*! \brief Inicializador do objeto "Transference Controller".
		 *		
		 *
		 *  O inicializador do objeto é padrão.
		 */
		TRcontroller();
		/*! \brief Função que envia o estado atual do jogo para o servidor.
		 *	
		 * \param j Arquivo json com o estado atual do jogo.
		 */
		void sendState(nlohmann::json j);
		/*! \brief Função que envia o estado atual do jogo para os clientes do servidor.
		 *	
		 * \param j Arquivo json com o estado atual do jogo.
		 * \param IP Endereço de ip do servidor do jogo.
		 */
		void sendState_server(nlohmann::json j, int porta);
		void checkConexion(int porta);
		void set_flag(int flag);
		std::vector<const char*> get_commands();
		nlohmann::json receiveState();
		void configServer();
		void configClient();
};

#endif
