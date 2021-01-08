#include "transfer_controller.h"

using boost::asio::ip::udp;

//!!! procurar um jeito de configurar sem depender de construtor
TRcontroller::TRcontroller(): local_endpoint(udp::v4(), 0), remote_endpoint(udp::v4(), 0), my_socket(my_io_service){}

void TRcontroller::sendState_server(nlohmann::json j) {

	//boost::asio::io_service my_io_service;

	//udp::endpoint local_endpoint(udp::v4(), porta);

	//udp::socket my_socket(my_io_service, local_endpoint);
	
	//std::string msg = j.dump();
	//char string[msg.size()+1];
	//strcpy(string, msg.c_str());
	//string[msg.size()]='\0';

	std::cout << "sending state..." << std::endl;
	for (int i = 0; i < remote_endpoints.size(); i++) {
		//my_socket.send_to(boost::asio::buffer(string, msg.size()+1), this->remote_endpoints[i]);
		sendJSON(j, remote_endpoints[i]);
	}
}

void TRcontroller::checkConnection(int porta) {

	char v[120];
	for (int i =0; i<1000; i++){v[i]='\0';}
	//char a[] = "{\"Cliente\":\"Cheguei\"}";
	//char b[] = "{\"Cliente\":\"Adeus\"}";

	char a[] = "Client: Cheguei";
	char b[] = "Client: Adeus";

	std::string msg;
	
	while(this->flag) {
		std::cout << "rodando o Server... " << std::endl;
		udp::endpoint remote_endpoint; // endpoint temporario

		my_socket.receive_from(boost::asio::buffer(v,120), remote_endpoint); // Confs. do Cliente

		if(strcmp(v, a) == 0) {
			(this->remote_endpoints).push_back(remote_endpoint);
			(this->commands).push_back("\0");
			msg = std::to_string(this->remote_endpoints.size());
			std::cout << "Cliente Adicionado: " << msg << std::endl;
			my_socket.send_to(boost::asio::buffer(msg), remote_endpoint);
		}

		else if(strcmp(v, b) == 0) {
			for (int i = 0; i < remote_endpoints.size(); i++) {
				if(this->remote_endpoints[i] == remote_endpoint) {
					(this->remote_endpoints).erase((this->remote_endpoints).begin() + i);
					this->commands[i] = "\n";
					std::cout << "Cliente Removido: " << i << std::endl;
					break;
				}
			}
		}

		// recebe comando do monitor
		else {
			for (int i = 0; i < remote_endpoints.size(); i++) {
				if(this->remote_endpoints[i] == remote_endpoint) {
					this->commands[i] = v;
					break;
				}
			}
		}
	}

}

std::vector<const char*>& TRcontroller::get_commands() {
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

	/*
	char recv[1000];
	for (int i =0; i<1000; i++){recv[i]='\0';}
	my_socket.receive_from(boost::asio::buffer(recv, 1000), remote_endpoint);
	std::cout << recv << std::endl;
	*/
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
	//remote_endpoint.port(0);

	std::string msg = j.dump();

	my_socket.send_to(boost::asio::buffer(msg), arg_remote_endpoint);

	/*
	char recv[1000];
	for (int i =0; i<1000; i++){recv[i]='\0';}
	my_socket.receive_from(boost::asio::buffer(recv, 1000), remote_endpoint);
	std::cout << recv << std::endl;
	*/
}

nlohmann::json TRcontroller::receiveJSON(){
	char recv[1000];
	for (int i =0; i<1000; i++){recv[i]='\0';}
	my_socket.receive_from(boost::asio::buffer(recv, 1000), remote_endpoint);
	nlohmann::json state = nlohmann::json::parse(recv);
	std::cout << state << std::endl;

	return nlohmann::json::parse(recv);
}

void TRcontroller::configServer(){
	std::cout << "Server Config" << std::endl;
	local_endpoint.port(9001);
	my_socket.open(udp::v4());
	my_socket.bind(local_endpoint);
	std::cout << local_endpoint << player_number << std::endl;
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
	char recv[1000];
	for (int i =0; i<1000; i++){recv[i]='\0';}
	my_socket.receive_from(boost::asio::buffer(recv, 1000), remote_endpoint);

	std::cout << "confirmacao do server: " << std::endl;
	std::cout << recv << std::endl;
	player_number = std::stoi(recv, nullptr);
	std::cout << "Numero do player: " << player_number << std::endl;
	std::cout << local_endpoint << player_number << std::endl;
	std::cout << remote_endpoint << player_number << std::endl;
}
