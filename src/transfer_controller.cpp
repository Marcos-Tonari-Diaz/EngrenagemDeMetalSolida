#include "transfer_controller.h"

using boost::asio::ip::udp;

TRcontroller::TRcontroller(): local_endpoint(udp::v4(), 0), remote_endpoint(udp::v4(), 0), my_socket(my_io_service){}

void TRcontroller::sendState_server(nlohmann::json j) {
	std::map<int, boost::asio::ip::udp::endpoint>::iterator ep;
	for (ep = remote_endpoints.begin(); ep!= remote_endpoints.end(); ++ep) {
		sendJSON(j, ep->second);
	}
}

void TRcontroller::checkConnection() {

	char v[5000];
	for (int i =0; i<5000; i++){v[i]='\0';}

	char a[] = "Client: Cheguei";
	char b[] = "Client: Adeus";

	std::string msg;

	int playerID = 1;
	
	while(this->flag) {
		//std::cout << "rodando a Server Thread... " << std::endl;
		udp::endpoint remote_endpoint; // endpoint temporario

		my_socket.receive_from(boost::asio::buffer(v,5000), remote_endpoint); // Confs. do Cliente

		if(strcmp(v, a) == 0) {
			remote_endpoints.insert({playerID,remote_endpoint});
			commands.insert({playerID,"new"});
			msg = std::to_string(playerID);
			std::cout << "Cliente Adicionado: " << msg << std::endl;
			my_socket.send_to(boost::asio::buffer(msg), remote_endpoint);
			playerID++;
		}

		else if(strcmp(v, b) == 0) {
			std::map<int, boost::asio::ip::udp::endpoint>::iterator ep;
			for (ep = remote_endpoints.begin(); ep!= remote_endpoints.end(); ++ep) {
				if(ep->second == remote_endpoint) {
					remote_endpoints.erase(ep->first);
					commands[ep->first] = "left";
					std::cout << "Cliente Removido: " << ep->first << std::endl;
					break;
				}
			}
		}

		// recebe comando do monitor
		else {
			std::map<int, boost::asio::ip::udp::endpoint>::iterator ep;
			for (ep = remote_endpoints.begin(); ep!= remote_endpoints.end(); ++ep) {
				if(ep->second == remote_endpoint) {
					commands[ep->first] = std::string(v);
					break;
				}
			}
		}
		// Clean the buffer
		for (int i =0; i<5000; i++){v[i]='\0';}
	}

}

std::map<int, std::string>& TRcontroller::get_commands() {
	return (this->commands);
}

void TRcontroller::set_flag(int flag) {
	this->flag = flag;
}

void TRcontroller::sendJSON(nlohmann::json j){
	// Encontrando IP remoto
	boost::asio::ip::address ip_remoto =
	boost::asio::ip::address::from_string("127.0.0.1");
	remote_endpoint.address(ip_remoto);

	// transformar string cpp em array de chars 
	std::string msg = j.dump();
	char string[msg.size()+1];
	strcpy(string, msg.c_str());
	string[msg.size()]='\0';

	my_socket.send_to(boost::asio::buffer(msg), this->remote_endpoint);
}

void TRcontroller::sendString(std::string msg){
	// Encontrando IP remoto
	boost::asio::ip::address ip_remoto =
	boost::asio::ip::address::from_string("127.0.0.1");
	remote_endpoint.address(ip_remoto);

	my_socket.send_to(boost::asio::buffer(msg), this->remote_endpoint);
}

void TRcontroller::sendJSON(nlohmann::json j, boost::asio::ip::udp::endpoint arg_remote_endpoint){
	// Encontrando IP remoto
	boost::asio::ip::address ip_remoto =
	boost::asio::ip::address::from_string("127.0.0.1");
	remote_endpoint.address(ip_remoto);

	std::string msg = j.dump();

	my_socket.send_to(boost::asio::buffer(msg), arg_remote_endpoint);
}

nlohmann::json TRcontroller::receiveJSON(){
	char recv[5000];
	for (int i =0; i<5000; i++){recv[i]='\0';}
	my_socket.receive_from(boost::asio::buffer(recv, 5000), remote_endpoint);

	return nlohmann::json::parse(recv);
}

void TRcontroller::configServer(){
	std::cout << "Server Config" << std::endl;
	local_endpoint.port(9001);
	my_socket.open(udp::v4());
	my_socket.bind(local_endpoint);
}

void TRcontroller::configClient(){
	std::cout << "Client" << std::endl;
	local_endpoint.port(0);
	my_socket.open(udp::v4());
	my_socket.bind(local_endpoint);

	// Encontrando IP remoto
	boost::asio::ip::address ip_remoto =
	boost::asio::ip::address::from_string("127.0.0.1");

	remote_endpoint.address(ip_remoto);
	remote_endpoint.port(9001);

	std::string v("Client: Cheguei");
	my_socket.send_to(boost::asio::buffer(v, v.size()), remote_endpoint);

	// Recebendo mensagem de retorno
	char recv[5000];
	for (int i =0; i<5000; i++){recv[i]='\0';}
	my_socket.receive_from(boost::asio::buffer(recv, 5000), remote_endpoint);

	std::cout << "confirmacao do server: " << std::endl;
	std::cout << recv << std::endl;
	player_number = std::stoi(recv, nullptr);
	std::cout << "Numero do player: " << player_number << std::endl;
}
