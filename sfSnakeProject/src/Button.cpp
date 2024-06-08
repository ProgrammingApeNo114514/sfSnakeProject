#include "Button.h"
#include <string>

using namespace sfSnake;

Button::Button() {}

Button::Button(const sf::Vector2f& position, const sf::Vector2f& scale, const std::string& filename)
{
	texture_.loadFromFile(filename);
	sprite_.setPosition(position);
	sprite_.setTexture(texture_);
	sprite_.setScale(scale);
	sf::FloatRect textBounds = sprite_.getLocalBounds();
	sprite_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
}

bool Button::MouseOnButton(sf::RenderWindow& window)
{
	if (sprite_.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		return true;

	return false;
}

bool Button::ButtonPressed(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) return true;

	return false;
}

void Button::render(sf::RenderWindow& window) const
{
	window.draw(sprite_);
}