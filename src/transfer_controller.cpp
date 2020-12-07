#include "transfer_controller.h"

using boost::asio::ip::udp;

void TRcontroller::send(nlohmann::json j, int IP) {
	char v[120];

	boost::asio::io_service my_io_service;

	udp::endpoint local_endpoint(udp::v4(), IP);

	udp::socket my_socket(my_io_service, local_endpoint);

	udp::endpoint remote_endpoint;
	
	my_socket.receive_from(boost::asio::buffer(v,120), remote_endpoint);

	std::string msg = j.dump();
	my_socket.send_to(boost::asio::buffer(msg), remote_endpoint);
}
