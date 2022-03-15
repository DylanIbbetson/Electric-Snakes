#include "Snake.h"
#include "Collectable.h"
#include <iostream>
#include "Battery.h"
#include <SFML/Graphics.hpp>



//A function that makes the snake move using the list of segments
void Snake::Move()
{
	if (SnakeAlive == true)
	{
		sf::Vector2f m_position = m_segments.front();

		//eNums that set the direction the snake is moving in
		switch (m_direction)
		{
		case Direction::eUp:
			m_position.y -= segment;
			break;
		case Direction::eDown:
			m_position.y += segment;
			break;
		case Direction::eRight:
			m_position.x += segment;
			break;
		case Direction::eLeft:
			m_position.x -= segment;
			break;
		default:
			break;
		}

		//Decreasing the grow amount of the snake and popping back the vector so the snake moves without infinitely growing
		m_segments.push_front(m_position);
		if (GrowAmount > 0)
		{
			GrowAmount--;
		}
		else
		{
			m_segments.pop_back();
		}
	}
	
}

//A function that changes the direction the snake is moving in
void Snake::ChangeDirection(Direction SnakeDirection)
{
	m_direction = SnakeDirection;
}

//A constructor that pushes back the segments into a list
Snake::Snake(sf::Vector2f position, sf::Color colour)
{
	m_segments.push_back(position);
	GrowAmount = 5;
	m_colour = colour;
}

//The function that renders the snake using the segments 
void Snake::render(sf::RenderWindow& window)
{
	sf::RectangleShape snake(sf::Vector2f(segment, segment));
	snake.setFillColor(m_colour);

	for (sf::Vector2f m_position : m_segments)
	{
		snake.setPosition(m_position);
		window.draw(snake);
	}

}

//A function that checks whether the collectables have been picked up by a snake or not
void Snake::CheckCollisions(std::vector<Collectable*>& m_collectables)
{
	for (Collectable* c : m_collectables)
	{
		if (c->Collected())
		{
			if (!m_segments.empty())
			{
				if (m_segments.front() == c->FindPosition())
				{
					GrowAmount = c->FindGrowAmount();
					m_score = m_score + c->FindScore();
					c->setInvisible();
					c->Kill();
				}
			}
			
		}
	}
}

//A function that checks whether the battery has been picked up by a snake or not
void Snake::CheckBatteryCollisions(std::vector<Battery*>& m_battery)
{
	for (Battery* c : m_battery)
	{
		if (c->Collected())
		{
			if (!m_segments.empty())
			{
				if (m_segments.front() == c->FindPosition())
				{
					m_score = m_score + c->FindScore();
					m_batteryActive = true;
					RestartTimer();
					c->setInvisible();
					c->Kill();
				}
			}
			
		}
	}
}

//Checking collisions of snakes hitting each other, working very similarly to the aura collisions
void Snake::CheckOtherCollisions(Snake& other)
{
	if (!this->getIsAlive())
	{
		return;
	}
	if (!other.getIsAlive())
	{
		return;
	}
	for (sf::Vector2f otherPosition : other.m_segments)
	{
		for (sf::Vector2f CurrentPosition : m_segments)
		{
			if (this->m_segments.front() == otherPosition)
			{
				this->Kill();
				m_score = m_score - 20;
			}
			else if (other.m_segments.front() == CurrentPosition)
			{
				other.Kill();
				other.m_score = other.m_score - 20;
			}
			else if (otherPosition == this->m_segments.front() && CurrentPosition == other.m_segments.front())
			{
				this->Kill();
				this->m_score = this->m_score - 20;

				other.Kill();
				other.m_score = other.m_score - 20;
			}
		}
	}
}


//A function that checks the collisions of the aura
void Snake::CheckAuraCollisions(Snake& other)
{
	if (!this->getIsAlive())
	{
		return;
	}
	if (!other.getIsAlive())
	{
		return;
	}
	for (sf::Vector2f CurrentPosition : m_aura)
	{
		for (sf::Vector2f OtherAura : other.m_aura)
		{
			for (sf::Vector2f otherPosition : other.m_segments)
			{
				for (sf::Vector2f Playersnake : m_segments)
				{

					//Checking if the position of the snakes overlap with the aura collisions, killing that snake if it does
					//Also increasing the score of the battery user, while decreasing the score of the snake that died
					if (otherPosition == CurrentPosition)
					{
						other.Kill();
						other.m_score = other.m_score - 20;
						m_score = m_score + 20;
						
					}
					else if (Playersnake == OtherAura)
					{
						Kill();
						this->m_score = this->m_score - 20;
						other.m_score = other.m_score + 20;
					}
				}
			}
		}
	}
}


//A function that creates a rectangle shape that is set to the same position as the segments making the snake
void Snake::AddAura(sf::RenderWindow& window)
{
	sf::RectangleShape Aura(sf::Vector2f(aura, aura));
	Aura.setFillColor(sf::Color(255,255,0,25));

	for (sf::Vector2f m_position : m_segments)
	{
		Aura.setPosition(m_position.x - (segment * 2), m_position.y - (segment * 2));

		//The position of the aura is set to cover both the x and y positions around the snake, then pushes the position into a vector
		auraPosition = sf::Vector2f(m_position.x + (segment * 2), m_position.y + (segment * 2));
		m_aura.push_back(auraPosition);
		auraPosition = sf::Vector2f(m_position.x - (segment * 2), m_position.y - (segment * 2));
		m_aura.push_back(auraPosition);

		window.draw(Aura);
	}
}

//A getter function that returns whether the battery is active or not
bool Snake::GetBatteryActive()
{
	return m_batteryActive;
} 

//Function that restarts the timer and then generates a random time for the next battery to be active for
void Snake::RestartTimer()
{
	m_BatteryTimer.restart();
	BatteryActiveTime = (rand() % 3000) + 1000;
}

//A function that checks the timer used by the battery collectable
//It disables the battery after a set amount of time and then clears the vector containing the aura
void Snake::CheckTimer()
{
	m_BatteryTime = m_BatteryTimer.getElapsedTime().asMilliseconds();
	if (m_BatteryTime >= BatteryActiveTime)
	{
		m_batteryActive = false;
		m_aura.empty();
	}
}

//A getter that returns the direction the snake is moving
void Snake::GetDirection()
{
	m_direction;
}

//A getter that returns the colour used by the snakes
sf::Color Snake::GetColour()
{
	return m_colour;
}

//A setter that sets the colour used by the snakes
void Snake::SetColour(sf::Color colour)
{
	m_colour = colour;
}

//A getter that returns whether the snake is alive or not
bool Snake::getIsAlive()
{
	return SnakeAlive;
}

//A getter function that returns the vector of segments
std::list<sf::Vector2f> Snake::GetSegments()
{
	return m_segments;
}


//This function checks the position of the snakes head against the x and y boundaries of the window space
void Snake::CheckWallCollisions(sf::RenderWindow& window)
{
	if (!m_segments.empty())
	{
		if (m_segments.front().x < 0)
		{
			WallCollision = true;
		}
		else if (m_segments.front().x > 885)
		{
			WallCollision = true;
		}
		else if (m_segments.front().y < 0)
		{
			WallCollision = true;
		}
		else if (m_segments.front().y > 885)
		{
			WallCollision = true;
		}

		if (WallCollision == true)
		{

			//Outputs a statement, kills the snake then decreases score
			std::cout << "Snake hit a wall, Game over!" << std::endl;
			Kill();
			m_score = m_score - 20;
		}
	}
	
}

//This function checks self collisions of the snakes, killing them if they hit themselves
void Snake::CheckSelfCollisions()
{
	bool front{ true };
	for (sf::Vector2f SegmentPos : m_segments)
	{
		if (front)
		{
			front = false;
			continue;
		}

		if (m_segments.front() == SegmentPos)
		{
			Kill();
			m_score = m_score - 20;
		}
					
	}

}

//This function gets all positions of all of the snakes
void Snake::GetAllPositions(std::vector<sf::Vector2f> AllSnakes)
{
	m_AllSnakePositions.clear();
	for (auto& snake : AllSnakes)
	{
		m_AllSnakePositions.push_back(snake);
	}
}

