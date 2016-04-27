#pragma once
#include <fstream>

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "session.h"

using boost::asio::ip::tcp;

class log_server
{
public:
	log_server(boost::asio::io_service& io_service, short port, const char* file_name);
	~log_server();

	void log_connected(const std::string& identifier, const int session_id);
	void log_disconnected(const std::string& identifier, const int session_id);
	void log(const std::string& msg, const int session_id);
private:
	void do_accept();
	void save_log(const std::string& msg);

	std::ofstream _logfile;
	tcp::socket _socket;
	tcp::acceptor _acceptor;
	int _id;
};