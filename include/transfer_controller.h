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
		std::map<int, boost::asio::ip::udp::endpoint> remote_endpoints;
		std::map<int, std::string> commands;
		int flag = 1;
	public:
		boost::asio::io_service my_io_service;
		udp::endpoint local_endpoint;
		udp::endpoint remote_endpoint;
		udp::socket my_socket;
		int player_number = 0;

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
		void sendJSON(nlohmann::json j);
		void sendString(std::string msg); 
		void sendJSON(nlohmann::json j, boost::asio::ip::udp::endpoint arg_remote_endpoint);
		nlohmann::json receiveJSON();
		/*! \brief Função que envia o estado atual do jogo para os clientes do servidor.
		 *	
		 * \param j Arquivo json com o estado atual do jogo.
		 * \param IP Endereço de ip do servidor do jogo.
		 */
		void sendState_server(nlohmann::json j);
		void checkConnection(int porta);
		void set_flag(int flag);
		std::map<int, std::string>& get_commands();
		void configServer();
		void configClient();
};

#endif
