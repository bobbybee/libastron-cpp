#include "global.h"

#include <boost/asio.hpp>

class Connection {
public:
	Connection(boost::asio::io_service* io_service, string host, uint16_t port);
private:
	string m_host;
	uint16_t m_port;
	boost::asio::ip::tcp::socket m_socket;
};