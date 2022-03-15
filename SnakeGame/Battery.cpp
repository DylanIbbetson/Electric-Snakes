#include "Battery.h"
#include <SFML/Graphics.hpp>

//A function to render the battery
void Battery::Render(sf::RenderWindow& window)
{
	sf::CircleShape food(7.5);
	food.setFillColor(sf::Color::Yellow);
	food.setPosition(m_position);
	window.draw(food);
}

//A constructor that sets the position of the first battery that spawns
Battery::Battery(sf::Vector2f m_pos) : m_position(m_pos)
{
	m_position.x = -20;
	m_position.y = -20;
}

//A function that sets each subsequent position of the battery after it has been collected, to a random position
void Battery::Spawn()
{
	int x = rand() % 30 * 30;
	int y = rand() % 30 * 30;

	m_position = sf::Vector2f((float)x, (float)y);
	m_value = rand() % 4 + 1;
	visible = true;
	m_collected = true;
}

//A function that sets the battery to be invisible after collecting it
bool Battery::setInvisible()
{
	visible = false;
	return visible;
}
