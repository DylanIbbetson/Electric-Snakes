#pragma once
#include <SFML/Graphics.hpp>

class Collectable
{
private:
	sf::Vector2f CollectablePos;
	int m_value = 0;
	bool m_collected = false;
	sf::Vector2f m_position;
	
	int m_score{ 10 };


public:
	bool visible = true;
	bool Collected() const { return m_collected; }
	void Render(sf::RenderWindow& window);

	Collectable(sf::Vector2f m_pos);

	void Spawn();
	void Kill() { m_collected = false; }

	//Getter and setter functions
	int FindGrowAmount() const { return m_value; }
	int FindScore() const { return m_score; }
	sf::Vector2f FindPosition() const { return m_position; }
	bool setInvisible();
};

