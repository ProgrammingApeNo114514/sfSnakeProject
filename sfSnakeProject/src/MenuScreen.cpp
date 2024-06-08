#include <memory>
#include <thread>
#include <chrono>
#include <string>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"
#include "Button.h"
#include "TextButton.h"
#include "HelpScreen.h"
#include "OptionScreen.h"

using namespace sfSnake;

const sf::Vector2f scale(0.15f * Game::Width / 1280, 0.15f * Game::Height / 960);

const sf::Vector2f optionbuttonposition(Game::Width / 4, Game::Height / 3 * 2);
const sf::Vector2f startbuttonposition(Game::Width / 2, Game::Height / 3 * 2);
const sf::Vector2f quitbuttonposition(Game::Width / 4 * 3, Game::Height / 3 * 2);

const sf::Vector2f helpbuttonposition(Game::Width - 75.f * Game::Width / 1280, 45.f * Game::Height / 960);

std::string startfilename1 = "materials/buttons/start1.png";
const std::string startfilename2 = "materials/buttons/start2.png";

const std::string quitfilename1 = "materials/buttons/quitbutton1.png";
const std::string quitfilename2 = "materials/buttons/quitbutton2.png";

const std::string optionfilename1 = "materials/buttons/optionbutton1.png";
const std::string optionfilename2 = "materials/buttons/optionbutton2.png";

MenuScreen::MenuScreen() :
	startbutton1(startbuttonposition, scale, startfilename1), startbutton2(startbuttonposition, scale, startfilename2),
	quitbutton1(quitbuttonposition, scale, quitfilename1), quitbutton2(quitbuttonposition, scale, quitfilename2),
	optionbutton1(optionbuttonposition, scale, optionfilename1), optionbutton2(optionbuttonposition, scale, optionfilename2)
{
	gamescreen = std::make_shared<GameScreen>();

	font_.loadFromFile("materials/Fonts/segoepr.ttf");

	snakeText_.setFont(font_);
	snakeText_.setString("Snake!");
	snakeText_.setColor(Game::GlobalTextColor);
	snakeText_.setCharacterSize(150);
	snakeText_.setStyle(sf::Text::Bold);

	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
		snakeTextBounds.top + snakeTextBounds.height / 2);
	snakeText_.setPosition(Game::Width / 2, Game::Height / 5);

	helpbutton = TextButton(sf::Vector2f(Game::Width - 75.f * Game::Width / 1280, 45.f * Game::Height / 960), std::string("Help"));
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	if (helpbutton.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		std::shared_ptr<MenuScreen> menuscreen = std::dynamic_pointer_cast<MenuScreen>(Game::Screen);
		Game::Screen = std::make_shared<HelpScreen>(menuscreen);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return;
	}

	if (startbutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		Game::Screen = gamescreen;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return;
	}

	if (optionbutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		std::shared_ptr<MenuScreen> menuscreen = std::dynamic_pointer_cast<MenuScreen>(Game::Screen);
		Game::Screen = std::make_shared<OptionScreen>(menuscreen, gamescreen);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return;
	}

	if (quitbutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) window.close();
}

void MenuScreen::update(sf::Time delta, sf::Time& generatefruitflag)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
}

void MenuScreen::render(sf::RenderWindow& window)
{
	window.clear(Game::GlobalBGColor);
	if (!quitbutton1.MouseOnButton(window))quitbutton1.render(window);
	else quitbutton2.render(window);

	if (!startbutton1.MouseOnButton(window))startbutton1.render(window);
	else startbutton2.render(window);

	if (!optionbutton1.MouseOnButton(window))optionbutton1.render(window);
	else optionbutton2.render(window);

	helpbutton.render(window);
	snakeText_.setColor(Game::GlobalTextColor);
	window.draw(snakeText_);
}