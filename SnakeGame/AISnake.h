#pragma once
#include "Snake.h"
#include <vector>


class AISnake : public Snake
{
private:


public:
	AISnake(sf::Vector2f position, sf::Color colour);
	bool PossibleSnakeCollisions(Direction NextDirection);
	void Update() override;



};

