#include "AISnake.h"
#include <SFML/Graphics.hpp>
#include <ctime>



AISnake::AISnake(sf::Vector2f position, sf::Color colour) : Snake(position, colour)
{
}


void AISnake::Update()
{
	bool PossibleMove = false;
	bool CheckedUp = false;
	bool CheckedDown = false;
	bool CheckedLeft = false;
	bool CheckedRight = false;



	if (!m_segments.empty())
	{
		while (!PossibleMove && getIsAlive())
		{
			Direction NextDirection = Direction::eUp;

			//Generatin a random direction for the next direction of the AI snake
			int randNum = (rand() % 4);

			if (randNum == 0)
			{
				NextDirection = Direction::eUp;
			}
			else if (randNum == 1)
			{
				NextDirection = Direction::eDown;
			}
			else if (randNum == 2)
			{
				NextDirection = Direction::eLeft;
			}
			else if (randNum == 3)
			{
				NextDirection = Direction::eRight;
			}

			//Is Up possible?
			if (NextDirection == Direction::eUp && m_direction != Direction::eDown && !PossibleSnakeCollisions(NextDirection))
			{
				m_direction = Direction::eUp;
				PossibleMove = true;
			}
			//Is up not possible?
			else if (NextDirection == Direction::eUp && (m_direction == Direction::eDown || PossibleSnakeCollisions(NextDirection)))
			{
				CheckedUp = true;
			}
			//Is down possible?
			else if (NextDirection == Direction::eDown && m_direction != Direction::eUp && !PossibleSnakeCollisions(NextDirection))
			{
				m_direction = Direction::eDown;
				PossibleMove = true;
			}
			//Is down not possible?
			else if (NextDirection == Direction::eDown && (m_direction == Direction::eUp || PossibleSnakeCollisions(NextDirection)))
			{
				CheckedDown = true;
			}
			//Is left possible?
			else if (NextDirection == Direction::eLeft && m_direction != Direction::eRight && !PossibleSnakeCollisions(NextDirection))
			{
				m_direction = Direction::eLeft;
				PossibleMove = true;
			}
			//Is left not possible?
			else if (NextDirection == Direction::eLeft && (m_direction == Direction::eRight || PossibleSnakeCollisions(NextDirection)))
			{
				CheckedLeft = true;
			}
			//Is right possible?
			else if (NextDirection == Direction::eRight && m_direction != Direction::eLeft && !PossibleSnakeCollisions(NextDirection))
			{
				m_direction = Direction::eRight;
				PossibleMove = true;
			}
			//Is right not possible?
			else if (NextDirection == Direction::eRight && (m_direction == Direction::eLeft || PossibleSnakeCollisions(NextDirection)))
			{
				CheckedRight = true;
			}
			else 
			{
				PossibleMove = false;
			}
			//If the snake is backed up into a corner or coiled around itself
			if ((CheckedUp && CheckedRight) && (CheckedDown && CheckedLeft))
			{
				Kill();
			}
		}

		
	}

	//Call the move function if the segments are not empty
	if (!m_segments.empty()) 
	{
		Move();
	}
}




//A function that checks one move ahead to see if the snake will collide with something on its next move
bool AISnake::PossibleSnakeCollisions(Direction NextDirection)
{
	for (sf::Vector2f segments : m_AllSnakePositions)
	{
		//Only making these checks if the segment vector is not empty
		if (!m_segments.empty())
		{
			//Returning true if moving up is not possible for the AI snake; returning false if it can move up
			if (NextDirection == Direction::eUp)
			{
				if (!GetBatteryActive() && (m_segments.front().y - segment) == segments.y && m_segments.front().x == segments.x)
				{
					return true;
				}
				else if ((m_segments.front().y - segment) < 0)
				{
					return true;
				}
				else
					return false;
			}
			//Returning true if moving down is not possible for the AI snake; returning false if it can move down
			else if (NextDirection == Direction::eDown)
			{
				if ((!GetBatteryActive()) && (m_segments.front().y + segment) == segments.y && m_segments.front().x == segments.x)
				{
					return true;
				}

				else if ((m_segments.front().y + segment) >= 900)
				{
					return true;
				}
				else
					return false;
			}	
			//Returning true if moving left is not possible for the AI snake; returning false if it can move left
			else if (NextDirection == Direction::eLeft)
			{
				if ((!GetBatteryActive()) && (m_segments.front().x - segment) == segments.x && m_segments.front().y == segments.y)
				{
					return true;
				}
				else if ((m_segments.front().x - segment) < 0)
				{
					return true;
				}
				else
					return false;
			}
			//Returning true if moving right is not possible for the AI snake; returning false if it can move right
			else if (NextDirection == Direction::eRight)
			{
				if ((!GetBatteryActive()) && (m_segments.front().x + segment) == segments.x && m_segments.front().y == segments.y)
				{
					return true;
				}
				else if ((m_segments.front().x + segment) >= 900)
				{
					return true;
				}
				else
					return false;
			}


		}
	}
}



	
