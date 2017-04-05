#include "Client.h"
#include <Game/Messages.h>
Client::Client(sf::TcpSocket* sock)
	: socket(sock)
{

}

Client::Client(Client&& rhs)
{
	this->id = rhs.id;
	this->latency = rhs.latency;
	this->socket = std::move(rhs.socket);
}

Client& Client::operator=(Client&& rhs)
{
	this->id = rhs.id;
	this->latency = rhs.latency;
	this->socket = std::move(rhs.socket);
	return *this;
}


void Client::Ping()
{
	sf::Packet ping;
	ping << NetworkMessages::PING;
	GetSocket().send(ping);

	timestamp = std::chrono::steady_clock::now();
}

void Client::Pong()
{
	auto end = std::chrono::steady_clock::now();
	latency = std::chrono::duration_cast
		<std::chrono::microseconds>
		(end - timestamp);
	latency /= 2;
}

unsigned int Client::next_id = 0;