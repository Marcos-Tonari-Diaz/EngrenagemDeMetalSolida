#include "transfer_controller.h"

using boost::asio::ip::udp;

//!!! procurar um jeito de configurar sem depender de construtor
TRcontroller::TRcontroller(): local_endpoint(udp::v4(), 0), remote_endpoint(udp::v4(), 0), my_socket(my_io_service){}

void TRcontroller::sendState(nlohmann::json j){
	// Encontrando IP remoto
	boost::asio::ip::address ip_remoto =
	boost::asio::ip::address::from_string("127.0.0.1");
	remote_endpoint.address(ip_remoto);
	//remote_endpoint.port(0);

	std::string msg = j.dump();
	my_socket.send_to(boost::asio::buffer(msg), remote_endpoint);

	char recv[1000];
	for (int i =0; i<1000; i++){recv[i]='\0';}
	my_socket.receive_from(boost::asio::buffer(recv, 1000), remote_endpoint);
	std::cout << recv << std::endl;
}

nlohmann::json TRcontroller::receiveState(){
	char recv[1000];
	for (int i =0; i<1000; i++){recv[i]='\0';}
	my_socket.receive_from(boost::asio::buffer(recv, 1000), remote_endpoint);
	nlohmann::json state = nlohmann::json::parse(recv);
	std::cout << state << std::endl;

	std::string msg("Server received msg");
	my_socket.send_to(boost::asio::buffer(msg), remote_endpoint);

	return nlohmann::json::parse(recv);
}

void TRcontroller::configServer(){
	std::cout << "Server Config" << std::endl;
	local_endpoint.port(9001);
	my_socket.open(udp::v4());
	my_socket.bind(local_endpoint);

	char recv[1000];
	for (int i =0; i<1000; i++){recv[i]='\0';}
	my_socket.receive_from(boost::asio::buffer(recv,1000), remote_endpoint);
	std::cout << recv << std::endl;

	std::string msg("Server handshake");
  	my_socket.send_to(boost::asio::buffer(msg), remote_endpoint);
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

	std::string v("Client handshake");
	my_socket.send_to(boost::asio::buffer(v, v.size()), remote_endpoint);

	// Recebendo mensagem de retorno
	char recv[1000];
	for (int i =0; i<1000; i++){recv[i]='\0';}
	my_socket.receive_from(boost::asio::buffer(recv, 1000), remote_endpoint);

	std::cout << "handshake do server: " << std::endl;
	std::cout << recv << std::endl;
}
