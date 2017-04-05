#pragma once
#include <iostream>
#include <future>
#include <string>

#include <SFML\Network.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"

using TCPClient = sf::TcpSocket;
using TCPClientPointer = std::unique_ptr<TCPClient>;
using TCPClientList = std::vector<TCPClientPointer>;
const sf::IpAddress S_IP("127.0.0.1");
constexpr int S_TCP_PORT(60010);

class Client
{
public:
	Client();
	~Client();

	void ClientHandle();
	void Render(TCPClient & socket);
	void ClientCommunication();
	bool Connect(TCPClient& socket);
	void HandleInput(TCPClient& socket, Player& _player, int _playerNum);
	
private:
	bool makeThread = true;
	std::thread thread;

	int playerNum = 0;
	int direction = 0;

	Player* player1;
	Player* player2;
	std::vector<Player*> playerStore;
	sf::Keyboard::Key keyPress = sf::Keyboard::B;
	std::atomic<int> playerDir;
};

