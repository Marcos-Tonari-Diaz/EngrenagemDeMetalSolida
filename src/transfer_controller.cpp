#include "transfer_controller.h"

using boost::asio::ip::udp;

void TRcontroller::sendState(nlohmann::json j, int porta) {
	char v[120];

	boost::asio::io_service my_io_service;

	udp::endpoint local_endpoint(udp::v4(), porta);

	udp::socket my_socket(my_io_service, local_endpoint);

	udp::endpoint remote_endpoint;
	
	my_socket.receive_from(boost::asio::buffer(v,120), remote_endpoint);

	std::string msg = j.dump();
	my_socket.send_to(boost::asio::buffer(msg), remote_endpoint);
}

nlohmann::json TRcontroller::receiveState() {
	
	std::string v("Cliente (Monitor) -> Servidor (Game)");

	boost::asio::io_service io_service;

	udp::endpoint local_endpoint(udp::v4(), 0);
	udp::socket meu_socket(io_service, local_endpoint);

	// Encontrando IP remoto
	boost::asio::ip::address ip_remoto =
	boost::asio::ip::address::from_string("127.0.0.1");

	udp::endpoint remote_endpoint(ip_remoto, 9001);

	meu_socket.send_to(boost::asio::buffer(v), remote_endpoint);

	//std::cout << v << std::endl;

	// Recebendo mensagem de retorno
	char recv[1000];
	meu_socket.receive_from(boost::asio::buffer(recv, 1000), remote_endpoint);

	std::cout << "Monitor recebeu estado como JSON" << std::endl;
	//std::cout << recv << std::endl;
	return nlohmann::json::parse(recv);
}

void configServer(){

}
