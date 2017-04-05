#include "GameClient.h"
#include "Client.h"
#include <SFML/Graphics.hpp>
#include "Client.h"

sf::RenderWindow window(sf::VideoMode(200, 200), "Tron Game!");
sf::CircleShape shape(100.f);
auto client = std::unique_ptr<Client>(new Client());

GameClient::GameClient()
{
}


GameClient::~GameClient()
{
}

void GameClient::Initialize()
{
	shape.setFillColor(sf::Color::Green);
	std::thread draw_thread(&GameClient::Draw, this);
	client->ClientThread();
	Draw();
	draw_thread.join();
}

void GameClient::Draw()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(shape);
		window.display();
	}
}
