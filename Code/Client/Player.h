#pragma once
//#include "Client.h"
#include <SFML/Graphics.hpp>

class Player : public sf::Sprite
{
public:
	Player(int _playerNum);
	~Player() = default;


	const float GetX() { return posX; }
	const float GetY() { return posY; }
	const int GetLives() { return lives; }
	const int GetSpeed() { return speed; }

	const sf::Sprite getSprite() { return playerSprite; }

	void SetLives(int _lives) { lives = _lives; }
	void SetSpeed(int _speed) { speed = _speed; }
	void SetPosX(int _posX) { posX = _posX; }
	void SetPosY(int _posY) { posY = _posY; }

	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();

	void MovePlayer(int _dir);

private:
	sf::Texture playerTexture;

	int lives = 0;
	float speed = 0.1f;
	float posX = 50.0f;
	float posY = 50.0f;

	sf::Sprite playerSprite;


};