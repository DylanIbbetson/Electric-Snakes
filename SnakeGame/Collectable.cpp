#include "Collectable.h"
#include <SFML/Graphics.hpp>

//A function to render the collectables
void Collectable::Render(sf::RenderWindow& window)
{
	sf::CircleShape food(7.5);
	food.setFillColor(sf::Color::Red);
	food.setPosition(m_position);
	window.draw(food);
}
//A constructor that sets the position of the inital collectable
Collectable::Collectable(sf::Vector2f m_pos) : 
	m_position(m_pos)
{
	m_position.x = -20;
	m_position.y = -20;
}

//A spawn function that randomises the position the collectable spawns at
void Collectable::Spawn()
{
	int x = rand() % 30 * 30;
	int y = rand() % 30 * 30;

	m_position = sf::Vector2f((float)x, (float)y);
	m_value = rand() % 4 + 1;
	visible = true;
	m_collected = true;
}

//A function that sets visible to true, so the collectable disappears after it has been collected
bool Collectable::setInvisible()
{
	visible = false;
	return visible;
}
