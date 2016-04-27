#include "tcp_client.h"
#include <ctime>

tcp_client::tcp_client(boost::asio::io_service* io, const char* host, const char* port)
: _io_service(io), _resolver(*_io_service), _query(host, port), _socket(*_io_service), _endpoint_iterator(_resolver.resolve(_query)), _connected(false)
{
	std::cout << "Logger initialized." << std::endl;

	boost::asio::async_connect(_socket, _endpoint_iterator,
		[&](const boost::system::error_code& ec, tcp::resolver::iterator i) ->
		void
	{
		if (!ec)
		{
			std::cout << "Logger connected." << std::endl;
			_connected = true;
		}
		else
			std::cout << "Logger connection failed. err_code: " << ec << ", err_msg: " << ec.message() << std::endl;
	});
}

tcp_client::~tcp_client()
{
	disconnect();
	std::cout << "Logger exits." << std::endl;
}

void tcp_client::log_message(const std::string& str)
{
	if (_connected)
	{
		std::time_t now = time(0);
		std::string time_str = std::ctime(&now);
		std::string send = time_str.substr(0, time_str.length()-1) + ": " + str;
		boost::asio::write(_socket, boost::asio::buffer(send));
	}
	else
		std::cout << "Couldn't log_message because the connection dropped or was never established." << std::endl;
}
	
void tcp_client::disconnect()
{
	std::string disconnect_cmd("DISCONNECT_ME_SAFELY");
	log_message(disconnect_cmd);
	_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
	_socket.close();
}