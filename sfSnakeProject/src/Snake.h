#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <deque>
#include <unordered_map>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
class Snake
{
public:
	Snake();

	void handleInput(sf::RenderWindow& window);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	void checkFruitCollisions(std::vector<Fruit>& fruits, std::unordered_map<Color, int>& fruitnum);

	bool hitSelf() const;

	unsigned getSize() const;

private:
	void move();
	void grow(const int& len);
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();

	bool hitSelf_;

	sf::Vector2f position_;
	sf::Vector2f direction_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	std::deque<SnakeNode> nodes_;
	sf::RectangleShape striation_;

	sf::Sprite head_;
	sf::Texture headtexture_;

	static const int InitialSize;
};
}

#endif