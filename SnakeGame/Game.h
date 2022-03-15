#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Snake;
class Collectable;
class Battery;

class Game
{
private:
	std::vector<Snake*> m_Snakes;
	std::vector<Collectable*> m_collectables;
	std::vector<Battery*> m_battery;
	std::vector<sf::Vector2f> AllSegments;
public:

	void Run();
	void GetAllSegmentPositions();
};

