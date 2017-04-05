#include "TronGame.h"
#include <SFML\Network.hpp>

sf::Packet& operator<<(sf::Packet& packet, const TronGame& game)
{
	packet << game.numPlayers;
	return packet;
}

sf::Packet& operator >> (sf::Packet& packet, TronGame& game)
{
	packet >> game.numPlayers;
	return packet;
}
