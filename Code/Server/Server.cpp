#include "Server.h"
#include "Client.h"
#include <Game\Messages.h>

Server::Server()
{
}


Server::~Server()
{
}

bool Server::ServerPort(sf::TcpListener & listener)
{
	if (listener.listen(S_TCP_PORT) != sf::Socket::Done)
	{
		std::cout << "Failed to bind server port: " << S_TCP_PORT << std::endl;
		return false;
	}
	return true;
}

void Server::Listen(sf::TcpListener & listener, sf::SocketSelector & socketSelector, TCPClientList & tcpClientList)
{
	while (true)
	{
		if (socketSelector.wait())
		{
			if (socketSelector.isReady(listener))
			{
				ConnectClient(listener, socketSelector, tcpClientList);
			}
			else
			{
				RecievePackets(tcpClientList, socketSelector);
			}
		}
	}
}

void Server::ConnectClient(sf::TcpListener & listener, sf::SocketSelector & socketSelector, TCPClientList & tcpClientList)
{
	auto  client_ptr = new sf::TcpSocket;
	auto& client_ref = *client_ptr;
	if (listener.accept(client_ref) == sf::Socket::Done)
	{
		socketSelector.add(client_ref);

		auto client = Client(client_ptr);
		tcpClientList.push_back(std::move(client));
		std::cout << "client connected" << std::endl;
		sf::Packet packet;
		packet << NetworkMessages::NUM_PLAYERS << tcpClientList.size();
		client_ref.send(packet);
	}
}

void Server::RecievePackets(TCPClientList & tcpClientList, sf::SocketSelector & socketSelector)
{
	for (auto& sender : tcpClientList)
	{
		auto& sender_socket = sender.GetSocket();
		if (socketSelector.isReady(sender_socket))
		{
			sf::Packet packet;
			if (sender_socket.receive(packet) == sf::Socket::Disconnected)
			{
				socketSelector.remove(sender_socket);
				sender_socket.disconnect();
				std::cout << "Client (" << sender.GetClientID()
					<< ") Disconnected" << std::endl;
				break;
			}

			int header = 0;
			packet >> header;

			NetworkMessages msg = static_cast<NetworkMessages>(header);
			if (msg == NetworkMessages::CHAT)
			{
				ProcessPacket(packet, sender, tcpClientList);
			}
			else if (msg == NetworkMessages::PONG)
			{
				sender.Pong();
			}
			else if (msg == NetworkMessages::DIRECTION)
			{
				ProcessPacket(packet, sender, tcpClientList);
			}
		}
	}
}

void Server::StartServer()
{
	sf::TcpListener listener;
	if (!ServerPort(listener))
	{
		return;
	}

	sf::SocketSelector socketSelector;
	socketSelector.add(listener);
	TCPClientList tcpClientList;
	return Listen(listener, socketSelector, tcpClientList);

}

void Server::Ping(TCPClientList& clients)
{
	constexpr auto timeout = 10s;
	for (auto& client : clients)
	{
		const auto& time = client.GetPing();
		const auto currentTime = std::chrono::steady_clock::now();
		auto deltaTime = currentTime - time;
		if (deltaTime > timeout)
		{
			client.Ping();
		}
	}
}

void Server::ClearClients(TCPClientList & tcp_clients)
{
	tcp_clients.erase(
		std::remove_if(tcp_clients.begin(), tcp_clients.end(), [](Client& client)
	{
		return(!client.isConnected());
	}), tcp_clients.end());
}

void Server::ProcessPacket(sf::Packet &packet, Client & sender, TCPClientList & tcp_clients)
{
	std::string string;
	packet >> string;

	// send the packet to other clients
	for (auto& client : tcp_clients)
	{
		if (sender == client)
			continue;

		client.GetSocket().send(packet);
	}
}