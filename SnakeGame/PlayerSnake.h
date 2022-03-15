#pragma once
#include "Snake.h"

class PlayerSnake : public Snake
{
public:
	PlayerSnake(sf::Vector2f position, sf::Color colour);
	void Update() override;
};

