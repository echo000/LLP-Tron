#pragma once
#include <chrono>
#include <memory>
#include <SFML/Network.hpp>

using namespace std::chrono_literals;
class Client
{
public:
	Client() = default;
	Client(sf::TcpSocket*);
	Client(Client&&);
	void Ping();
	void Pong();


	sf::TcpSocket& GetSocket() { return *socket; }
	bool isConnected() { return socket->getLocalPort() != 0; };
	void SetLatency(std::chrono::microseconds duration) { latency = duration; }
	const auto& GetPing() const { return timestamp; }
	const auto& GetLatency()  const { return latency; }
	int GetClientID()         const { return id; }

	Client& operator=(Client&&);
	bool operator==(const Client& rhs) { return id == rhs.id; }

private:
	static unsigned int next_id;

	std::unique_ptr<sf::TcpSocket> socket = nullptr;
	std::chrono::steady_clock::time_point timestamp = std::chrono::steady_clock::now();
	std::chrono::microseconds latency = 100us;
	int id = next_id++;
};