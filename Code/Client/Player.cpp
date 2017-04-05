#include "Player.h"


Player::Player(int _playerNum)
{

	if (!playerTexture.loadFromFile("..\\..\\Resources\\Bike.png"))
	{
		return;
	}

	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(this->GetX(), this->GetY());
	return;

	/*if (_playerNum == 1)
	{
		if (!playerTexture.loadFromFile("..\\..\\Resources\\Bike.png"))
		{
			return;
		}

		playerSprite.setTexture(playerTexture);
		playerSprite.setPosition(this->GetX(), this->GetY());
		return;
	}
	else if (_playerNum == 2)
	{
		if (!playerTexture.loadFromFile("..\\..\\Resources\\Bike.png"))
		{
			return;
		}

		playerSprite.setTexture(playerTexture);
		playerSprite.setPosition(400.0f, 400.0f);
		return;
	}*/

}

void Player::MoveRight()
{
	playerSprite.move(sf::Vector2f(0.1f * speed, 0));
}

void Player::MoveLeft()
{
	playerSprite.move(sf::Vector2f(-0.1f * speed, 0));
}

void Player::MoveUp()
{
	playerSprite.move(sf::Vector2f(0, -0.1f * speed));
}

void Player::MoveDown()
{
	playerSprite.move(sf::Vector2f(0, 0.1f * speed));
}

void Player::MovePlayer(int _dir)
{
	if (_dir == 1)
	{
		this->MoveLeft();
	}
	else if (_dir == 2)
	{
		this->MoveRight();
	}
	else if (_dir == 3)
	{
		this->MoveUp();
	}
	else if (_dir == 4)
	{
		this->MoveDown();
	}
}
