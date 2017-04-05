#pragma once
#include <SFML/Network.hpp>
enum NetworkMessages : sf::Int32
{

	INVALID = 0,
	CHAT = 1,
	PING = 2,
	PONG = 3,
	CLIENT_COUNT = 4,
	NUM_PLAYERS = 5,
	CLIENT_CONNECTED = 6,
	DIRECTION = 7
};