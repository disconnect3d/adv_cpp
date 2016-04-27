#include "log_server.h"
#include <sstream>

log_server::log_server(boost::asio::io_service& io_service, short port, const char* file_name)
: _acceptor(io_service, tcp::endpoint(tcp::v4(), port)), _socket(io_service), _id(0), _logfile(file_name, std::ofstream::out)
{
	std::cout << "Log server started" << std::endl;
	do_accept();
}

log_server::~log_server()
{
	std::cout << "Log server exits." << std::endl;
	_logfile.close();
}

void log_server::do_accept()
{
	_acceptor.async_accept(_socket, [this](boost::system::error_code ec)
	{
		if (!ec)
			std::make_shared<session>(std::move(_socket), *this, _id++)->start();
		
		do_accept();
	}
	);
}

void log_server::log_connected(const std::string& identifier, const int session_id)
{
	std::stringstream ss;
	ss << "Client connected: " << identifier << ", assigned session id (SID): " << session_id << "\n";
	
	save_log(ss.str());
}

void log_server::log_disconnected(const std::string& identifier, const int session_id)
{
	std::stringstream ss;
	ss << "Client disconnected: " << identifier << ", SID: " << session_id << "\n";
	
	save_log(ss.str());
}

void log_server::log(const std::string& msg, const int session_id)
{
	std::stringstream ss;
	ss << "[SID:" << session_id << "]: " << msg << "\n";

	save_log(ss.str());
}

void log_server::save_log(const std::string& msg)
{
	std::cout << msg;
	std::cout.flush();

	_logfile << msg;
	_logfile.flush();
}
