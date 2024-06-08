#ifndef OPTIONSCREEN_H
#define OPTIONSCREEN_H

#include <SFML/Graphics.hpp>

#include "PauseScreen.h"
#include "Game.h"
#include "Button.h"
#include "TextButton.h"
#include "MenuScreen.h"

namespace sfSnake
{
	class OptionScreen : public Screen
	{
	public : 
		OptionScreen(std::shared_ptr<PauseScreen>& pausescreen);
		OptionScreen(std::shared_ptr<MenuScreen>& menuscreen, std::shared_ptr<GameScreen>& gamescreen);

		void handleInput(sf::RenderWindow& window) override;
		void update(sf::Time delta, sf::Time& generatefruitflag) override;
		void render(sf::RenderWindow& window) override;

	private:
		sf::Font font_;
		
		sf::Text optiontext_;
		sf::Color bgcolor;
		std::shared_ptr<PauseScreen> pausescreen_;
		std::shared_ptr<MenuScreen> menuscreen_;
		std::shared_ptr<GameScreen> gamescreen_;

		Button gobackbutton1;
		Button gobackbutton2;

		sf::Text optionlist_;

		TextButton grid_on; 
		TextButton grid_off;

		TextButton grid_black;
		TextButton grid_white;
		TextButton grid_brown;

		TextButton bg_black;
		TextButton bg_white;
		TextButton bg_brown;
	};
}

#endif 
