#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <stdbool.h>
#include <iostream>
namespace sfSnake {
	class Button
	{
	public:
		Button();
		Button(const sf::Vector2f& position, const sf::Vector2f& scale, const std::string& filename);

		bool MouseOnButton(sf::RenderWindow& window);
		bool ButtonPressed(sf::RenderWindow& window);
		
		void render(sf::RenderWindow& window) const;
	private:
		sf::Sprite sprite_;
		sf::Texture texture_;
	};
}
#endif