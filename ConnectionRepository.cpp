#include "ConnectionRepository.h"

vector<string> astron_keywords {"clsend", "ownsend", "clrecv", "ownrecv",
                               "airecv", "broadcast", "ram", "required", "db"};

ConnectionRepository::ConnectionRepository(boost::asio::io_service* io_service, string host, uint16_t port, string dcFile) : 
												m_dcFile(dcFile),
												m_host(host),
												m_port(port),
												m_connection(Connection(io_service, host, port))
{
	cout << "Initializing ConnectionRepository with dcFile " << dcFile << endl;
	
	m_module = new Module();

	for(string keyword : astron_keywords) {
        m_module->add_keyword(keyword);
    }

    parse_dcfile(m_module, m_dcFile);
}

void ConnectionRepository::send(Datagram dg) {
	m_connection.send(dg);
}

void ConnectionRepository::close() {
	m_connection.close();
}

void ConnectionRepository::on_data(uint8_t* data, uint16_t len) {
	Datagram dg(data, len);
	DatagramIterator di(dg);

	uint8_t num_recipients = di.read_uint8();
	vector<uint64_t> recipients;

	while(num_recipients--) {
		uint64_t recipient = di.read_uint64();
		recipients.push_back(recipient);
	}

	uint64_t sender = di.read_uint64();
	uint16_t msgtype = di.read_uint16();

	cout << sender << " sent " << msgtype << " to " << recipients[0] << endl;
}

void ConnectionRepository::loop() {
	m_connection.poll(
		[&](uint8_t* data, uint16_t len) {
			on_data(data, len);
		}
	);
}