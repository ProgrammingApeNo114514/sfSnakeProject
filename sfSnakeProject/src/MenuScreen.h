#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "TextButton.h"
#include "Button.h"
#include "GameScreen.h"
#include <memory>

namespace sfSnake
{
class MenuScreen : public Screen
{
public:
	MenuScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta, sf::Time& generatefruiflag) override;
	void render(sf::RenderWindow& window) override;

private:
	sf::Font font_;
	sf::Text snakeText_;

	std::shared_ptr<GameScreen> gamescreen; 

	TextButton helpbutton;

	Button optionbutton1;
	Button optionbutton2;

	Button quitbutton1;
	Button quitbutton2;

	Button startbutton1;
	Button startbutton2;
};
}

#endif