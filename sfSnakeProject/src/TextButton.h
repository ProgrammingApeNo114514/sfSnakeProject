#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include <SFML/Graphics.hpp>
#include <stdbool.h>

namespace sfSnake {
	class TextButton
	{
	public:
		TextButton();
		TextButton(const sf::Vector2f& position, const std::string& text);

		bool MouseOnButton(sf::RenderWindow& window);
		bool ButtonPressed(sf::RenderWindow& window);

		void render(sf::RenderWindow& window);

		void ChangeColor(sf::Color color);
		sf::Color GetColor();

		void operator=(const TextButton& button);
	private:
		sf::Text text_;
		sf::Font font_;
	};
}

#endif  
