#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
	enum class Color
	{
		Black, Brown, Red, Green, Blue
	};
class Fruit
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0), sf::Color color = sf::Color::Black, Color enumcolor = Color::Black);
	
	void render(sf::RenderWindow& window);
	Color Getfruitcolor();

	sf::FloatRect getBounds() const;

private:
	sf::CircleShape shape_;
	Color fruitcolor;

	static const float Radius;
};
}

#endif