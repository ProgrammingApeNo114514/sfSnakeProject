#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include <SFML/Graphics.hpp>

#include "GameScreen.h"
#include "Game.h"
#include "Button.h"
#include "TextButton.h"

namespace sfSnake
{
	class PauseScreen : public Screen
	{
	public:
		PauseScreen(std::shared_ptr<GameScreen>& gamescreen, const int& score);

		void handleInput(sf::RenderWindow& window) override;
		void update(sf::Time delta, sf::Time& generatefruitflag) override;
		void render(sf::RenderWindow& window) override;

		std::shared_ptr<GameScreen> GetGameScreen();

	private:
		sf::Font font_;

		sf::Text pausetext_;
		sf::Text scoretext_;

		sf::Color bgcolor;
		std::shared_ptr<GameScreen> gamescreen_;

		Button continuebutton1;
		Button continuebutton2;

		Button optionbutton1;
		Button optionbutton2;

		Button restartbutton1;
		Button restartbutton2;

		Button quitbutton1;
		Button quitbutton2;

		TextButton helpbutton;
	};
}

#endif