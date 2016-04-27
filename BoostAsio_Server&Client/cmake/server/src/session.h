#pragma once

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>

#include <memory>

class log_server;

using boost::asio::ip::tcp;

class session
	: public std::enable_shared_from_this<session>
{
public:
	session(tcp::socket socket, log_server& server, const int id);

	void start();

private:
	void do_read();
	void log(const std::string& msg) const;
	
	tcp::socket _socket;
	enum { max_length = 1024 };
	char _data[max_length];

	log_server& _server;
	const int _id;
	std::string _ip;
};


/*
void do_write(std::size_t length) {
auto self(shared_from_this());
boost::asio::async_write(
socket_,
boost::asio::buffer(data_, length),
[this, self](boost::system::error_code ec, std::size_t length)
{
if (!ec) {
do_read();
}
}
);
}*/
