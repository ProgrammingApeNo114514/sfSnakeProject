#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Button.h"
#include "TextButton.h"

namespace sfSnake
{
class GameOverScreen : public Screen
{
public:
	GameOverScreen(std::size_t score);

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta, sf::Time& generatefruitflag) override;
	void render(sf::RenderWindow& window) override;

private:
	sf::Font font_;
	sf::Text text_;

	Button quitbutton1;
	Button quitbutton2;
	
	Button restartbutton1;
	Button restartbutton2;

	TextButton menu;

	unsigned score_;
};
}

#endif