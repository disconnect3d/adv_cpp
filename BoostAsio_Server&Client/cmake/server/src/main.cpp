#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

#include "log_server.h"

using boost::asio::ip::tcp;


int main(int argc, char* argv[])
{
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: async_tcp_echo_server <port> <logfile name>\n";
			return 1;
		}

		boost::asio::io_service io_service;
		log_server s(io_service, std::atoi(argv[1]), argv[2]);
		io_service.run();
	}

	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}