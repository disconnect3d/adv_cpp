#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "tcp_client.h"


/////////////////////////////////////////////////////////////////////////////////////////////
// Code below is used to handle CTRL+C signal/interrupt to safely close connection
/////////////////////////////////////////////////////////////////////////////////////////////
tcp_client* signal_client_ptr;
bool connected = true;

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
BOOL WINAPI signal_handler(_In_ DWORD dwCtrlType)
{
	connected = false;
	return true;
}
#else // UNIX
#include <csignal>
#include <cstdlib>
#include <cstdio>

void signal_handler(int)
{
	connected = false;
}
#endif // ifdef WIN32
/////////////////////////////////////////////////////////////////////////////////////////////

using boost::asio::ip::tcp;


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Usage: <host> <port>" << std::endl;
		return 0;
	}

	try
	{
		boost::asio::io_service io_service;
		
		tcp_client logger(&io_service, argv[1], argv[2]);

		/////////////////////////////////////////////////////////////////////////////////////////////
		// Code below is used to handle CTRL+C signal to safely close connection
		/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef WIN32
        signal(SIGINT, signal_handler);
#else
		SetConsoleCtrlHandler(signal_handler, TRUE);
#endif
		/////////////////////////////////////////////////////////////////////////////////////////////

		io_service.run();

		while (connected)
		{
			std::string str;
			std::cin >> str;
			if (connected)	// this may not really be necessary, but I felt like the log_message was called in wrong time sometimes.
				logger.log_message(str);
			else
				break;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
