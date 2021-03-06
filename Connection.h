#ifndef __CONNECTION_H_INCLUDED_
#define __CONNECTION_H_INCLUDED_

#include "global.h"

#include <boost/asio.hpp>

class Connection {
public:
	Connection(boost::asio::io_service* io_service, string host, uint16_t port);
	void send(Datagram dg);
	void close();
	void poll(function<void(uint8_t* data, uint16_t len)> on_data);
private:
	string m_host;
	uint16_t m_port;
	shared_ptr<boost::asio::ip::tcp::socket> m_socket;
};

#endif