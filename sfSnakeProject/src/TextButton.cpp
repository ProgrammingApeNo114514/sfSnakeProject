#include "TextButton.h"
#include "Game.h"

#include <string>

using namespace sfSnake;

TextButton::TextButton() {}

TextButton::TextButton(const sf::Vector2f& position, const std::string& text)
{
	font_.loadFromFile("materials/Fonts/segoepr.ttf");
	text_.setFont(font_);
	text_.setString(text);
	text_.setColor(sf::Color::White);
	text_.setOutlineColor(sf::Color::Black);
	text_.setOutlineThickness(1.f);
	text_.setCharacterSize(Game::TextSize);
	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2, 0);
	text_.setPosition(position);
}

bool TextButton::MouseOnButton(sf::RenderWindow& window)
{
	if (text_.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		return true;

	return false;
}

bool TextButton::ButtonPressed(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) return true;

	return false;
}

void TextButton::render(sf::RenderWindow& window) 
{
	if (text_.getColor() != Game::OptionSelectedColor &&
		text_.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		text_.setColor(Game::OptionFocusedColor);
		window.draw(text_);
		text_.setColor(sf::Color::White);
	}
	else
	{
		window.draw(text_);
	}
}

void TextButton::ChangeColor(sf::Color color)
{
	text_.setColor(color);
}

sf::Color TextButton::GetColor()
{
	return text_.getColor();
}

void TextButton::operator=(const TextButton& button)
{
	font_.loadFromFile("materials/Fonts/segoepr.ttf");
	text_.setFont(font_);
	text_.setString(button.text_.getString());
	text_.setPosition(button.text_.getPosition());
	text_.setColor(sf::Color::White);
	text_.setOutlineColor(Game::GlobalTextColor);
	text_.setOutlineThickness(1.f);
	text_.setCharacterSize(Game::TextSize);
	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2, 0);
}