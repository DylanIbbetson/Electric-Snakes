#include "PlayerSnake.h"
#include <SFML/Graphics.hpp>

PlayerSnake::PlayerSnake(sf::Vector2f position, sf::Color colour) : Snake(position, colour)
{
}

//Player movement inside the update function
//Detecting key presses and changing the direction of the snake based on the key press
void PlayerSnake::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_direction != (Direction::eDown))
	{
		ChangeDirection(Direction::eUp);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_direction != (Direction::eUp))
	{
		ChangeDirection(Direction::eDown);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_direction != (Direction::eRight))
	{
		ChangeDirection(Direction::eLeft);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_direction != (Direction::eLeft))
	{
		ChangeDirection(Direction::eRight);
	}	

	Move();
}
