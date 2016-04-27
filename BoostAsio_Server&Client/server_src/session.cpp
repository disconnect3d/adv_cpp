#include "session.h"
#include "log_server.h"

session::session(tcp::socket socket, log_server& server, const int id)
: _socket(std::move(socket)), _server(server), _id(id), _ip(_socket.remote_endpoint().address().to_string())
{
	//std::memset(data_, 0, sizeof(*data_)*max_length); // it is not required
	_server.log_connected(_ip, _id);
}

void session::start() {
	do_read();
}

void session::log(const std::string& msg) const
{
	_server.log(msg, _id);
}

void session::do_read()
{
	auto self(shared_from_this());
	_socket.async_read_some(boost::asio::buffer(_data, max_length),
		[this, self](boost::system::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			_data[length < max_length? length : max_length-1] = '\0';
			
			std::string data_str(_data);

			std::string disconnect_cmd = "DISCONNECT_ME_SAFELY";
			if (data_str.length() > disconnect_cmd.length() && 
				!data_str.compare(data_str.length() - disconnect_cmd.length(), data_str.length() - 1, disconnect_cmd))
			{
				_socket.shutdown(tcp::socket::shutdown_both);
				_socket.close();
				_server.log_disconnected(_ip, _id);
				return;
			}
			else
				_server.log(data_str, _id);
			
			do_read();
		}
	});
}