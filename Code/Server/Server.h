#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <SFML/Network.hpp>
#include "Client.h"


constexpr int S_TCP_PORT(60010);
constexpr int S_UDP_PORT(60010);

using TCPClient = sf::TcpSocket;
using TCPClientPointer = std::unique_ptr<TCPClient>;
using TCPClientList = std::vector<Client>;

class Server
{
public:
	Server();
	~Server();

	bool ServerPort(sf::TcpListener& listener);
	void Listen(sf::TcpListener& listener, sf::SocketSelector& socketSelector, TCPClientList& tcpClientList);
	void ConnectClient(sf::TcpListener& listener, sf::SocketSelector& socketSelector, TCPClientList& tcpClientList);
	void RecievePackets(TCPClientList& tcpClientList, sf::SocketSelector& socketSelector);
	void StartServer();
	void Ping(TCPClientList & clients);
	void ClearClients(TCPClientList & tcp_clients);
	void ProcessPacket(sf::Packet & packet, Client& sender, TCPClientList & tcp_clients);
};

