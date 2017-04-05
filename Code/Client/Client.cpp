#include "Client.h"
#include <Game/Messages.h>

Client::Client()
{
}

Client::~Client()
{
}


void Client::ClientHandle()
{
	TCPClient socket;

	if (!Connect(socket))
	{
		return;
	}
	std::future<void> handle = std::async(std::launch::async, [&]
	{
		sf::Socket::Status status;
		do
		{
			sf::Packet packet;
			status = socket.receive(packet);
			if (makeThread == true)
			{
				makeThread = false;
				thread = std::thread(&Client::ClientCommunication, this);
				thread.detach();
			}
			if (status == sf::Socket::Done)
			{
				int packetStore = 0;
				packet >> packetStore;
				NetworkMessages msg = static_cast<NetworkMessages>(packetStore);

				if (msg == NetworkMessages::NUM_PLAYERS)
				{
					int size = 0;
					packet >> size;
					if (size == 1)
					{
						playerNum = 1;
					}
					if (size == 2)
					{
						playerNum = 2;
						sf::Texture playerTexture2;
						if (!playerTexture2.loadFromFile("..\\..\\Resources\\Bike.png"))
						{
							return;
						}
					}
				}
				if (msg == NetworkMessages::DIRECTION)
				{
					int dir = 0;
					packet >> dir;
					playerDir = dir;
				}
			}

		} while (status != sf::Socket::Disconnected);

	});
	return Render(socket);
}

void Client::Render(TCPClient& socket)
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Bike racer");

	player1 = new Player(playerNum);
	playerStore.push_back(player1);

	player2 = new Player(playerNum);
	playerStore.push_back(player2);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

		}
		if (playerNum == 1)
		{
			HandleInput(socket, *player1, playerNum);
		}
		else if (playerNum == 2)
		{
			HandleInput(socket, *player2, playerNum);
		}

		window.clear();

		for (std::vector<Player*>::iterator i = playerStore.begin(); i != playerStore.end(); i++)
		{
			window.draw((*i)->getSprite());
		}
		window.display();
	}
}

void Client::ClientCommunication()
{
	while (true)
	{
		if (player2 != nullptr)
		{
			player2->MovePlayer(playerDir);
			std::this_thread::sleep_for(std::chrono::nanoseconds(620));
		}
	}
}

bool Client::Connect(TCPClient & socket)
{
	sf::Socket::Status status = socket.connect(S_IP, S_TCP_PORT);
	if (status != sf::Socket::Status::Done)
	{
		return false;
	}
	return true;
}

void Client::HandleInput(TCPClient& socket, Player& _player, int _playerNum)
{

	sf::Packet packet;

	if (_playerNum == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || keyPress == sf::Keyboard::A)
		{
			if (direction != 1)
			{
				direction = 1;
				packet << NetworkMessages::DIRECTION << direction;
				socket.send(packet);
			}

			_player.MoveLeft();
			keyPress = sf::Keyboard::A;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || keyPress == sf::Keyboard::D)
		{
			if (direction != 2)
			{
				direction = 2;
				packet << NetworkMessages::DIRECTION << direction;
				socket.send(packet);
			}

			_player.MoveRight();
			keyPress = sf::Keyboard::D;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || keyPress == sf::Keyboard::W)
		{
			if (direction != 3)
			{
				direction = 3;
				packet << NetworkMessages::DIRECTION << direction;
				socket.send(packet);
			}

			_player.MoveUp();
			keyPress = sf::Keyboard::W;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || keyPress == sf::Keyboard::S)
		{
			if (direction != 4)
			{
				direction = 4;
				packet << NetworkMessages::DIRECTION << direction;
				socket.send(packet);
			}

			_player.MoveDown();
			keyPress = sf::Keyboard::S;
		}
	}
	else if (_playerNum == 2)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) || keyPress == sf::Keyboard::F)
		{
			_player.MoveLeft();
			keyPress = sf::Keyboard::F;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) || keyPress == sf::Keyboard::H)
		{
			_player.MoveRight();
			keyPress = sf::Keyboard::H;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) || keyPress == sf::Keyboard::T)
		{
			_player.MoveUp();
			keyPress = sf::Keyboard::T;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) || keyPress == sf::Keyboard::G)
		{
			_player.MoveDown();
			keyPress = sf::Keyboard::G;
		}
	}

}