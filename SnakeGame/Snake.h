#pragma once
#include <SFML/Graphics.hpp>
#include <list>
//#include "Collectable.h"
//#include "Battery.h"

enum class Direction
{
	eUp,
	eDown,
	eRight,
	eLeft
};

class Collectable;
class Battery;

class Snake
{
private:
	
	sf::Vector2f m_position;
	int GrowAmount;
	
	//bool front{ true };
	int m_score{ 0 };


protected:

	
	sf::Clock m_BatteryTimer;

	float m_BatteryTime{0};
	bool m_batteryActive{ false };

	std::vector<sf::Vector2f> m_aura;
	sf::Vector2f auraPosition;

	std::vector<sf::Vector2f> m_AllSnakePositions;

	bool WallCollision{ false };
	void Move();
	void ChangeDirection(Direction SnakeDirection);
	std::list<sf::Vector2f> m_segments;
	sf::Color m_colour;

	int segment{ 15 };
	int aura{ 75 };
	float BatteryActiveTime;

public:
	
	Snake(sf::Vector2f position, sf::Color colour);

	virtual void Update() = 0;
	virtual void render(sf::RenderWindow& window);

	//Collision functions
	void CheckCollisions(std::vector<Collectable*>& m_collectables);
	void CheckSelfCollisions();
	void CheckWallCollisions(sf::RenderWindow& window);
	void CheckBatteryCollisions(std::vector<Battery*>& m_battery);
	void CheckOtherCollisions(Snake& other);
	void CheckAuraCollisions(Snake& other);

	//Battery functions
	void AddAura(sf::RenderWindow& window);
	bool GetBatteryActive();

	void RestartTimer();
	void CheckTimer();

	Direction m_direction{ Direction::eUp };
	
	//Getter and setter functions
	void GetDirection();	
	bool getIsAlive();
	int FindScore() const { return m_score; }
	sf::Color GetColour();
	void SetColour(sf::Color colour);
	std::list<sf::Vector2f> GetSegments();
	void GetAllPositions(std::vector<sf::Vector2f> AllSnakes);
	
	void Kill() { SnakeAlive = false; }

	bool SnakeAlive{ true };
	

};

