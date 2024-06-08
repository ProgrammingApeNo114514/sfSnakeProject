#ifndef HELPSCREEN_H
#define HELPSCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Button.h"
#include "PauseScreen.h"
#include "MenuScreen.h"

namespace sfSnake {
	class HelpScreen : public Screen
	{
	public:
		HelpScreen();
		HelpScreen(std::shared_ptr<PauseScreen>& pausescreen);
		HelpScreen(std::shared_ptr<MenuScreen>& menuscreen);

		void handleInput(sf::RenderWindow& window) override;
		void update(sf::Time delta, sf::Time& generatefruitflag) override;
		void render(sf::RenderWindow& window) override;
	private:
		Button gobackbutton1;
		Button gobackbutton2;

		sf::Font font_;
		sf::Text helptext_;
		sf::Text contenttext_;

		std::shared_ptr<PauseScreen> pausescreen_;
		std::shared_ptr<MenuScreen> menuscreen_;
	};
}

#endif 
