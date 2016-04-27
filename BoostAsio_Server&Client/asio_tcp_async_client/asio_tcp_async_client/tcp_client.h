#pragma once

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
#define _CRT_SECURE_NO_WARNINGS

class tcp_client
{
public:
	// Initializes connection
	tcp_client(boost::asio::io_service* io, const char* host, const char* port);
	~tcp_client();

	// Logs message async
	void log_message(const std::string& str);

	// Safely disconnects
	void disconnect();

private:
	void wait_for_logs_loop();
	
	boost::asio::io_service* _io_service;
	tcp::resolver _resolver;
	tcp::resolver::query _query;
	tcp::socket _socket;
	tcp::resolver::iterator _endpoint_iterator;
	bool _connected;
};