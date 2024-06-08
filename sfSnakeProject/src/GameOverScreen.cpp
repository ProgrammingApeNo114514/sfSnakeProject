#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "MenuScreen.h"

using namespace sfSnake;

const sf::Vector2f otherbuttonscale(0.15f * Game::Width / 1280, 0.15f * Game::Height / 960);

const sf::Vector2f quitbuttonposition(Game::Width / 2 + Game::Width / 6, Game::Height / 3 * 2);
const sf::Vector2f restartbuttonposition(Game::Width / 2 - Game::Width / 6, Game::Height / 3 * 2);

const std::string restartfilename1 = "materials/buttons/restartbutton1.png";
const std::string restartfilename2 = "materials/buttons/restartbutton2.png";

const std::string quitfilename1 = "materials/buttons/quitbutton1.png";
const std::string quitfilename2 = "materials/buttons/quitbutton2.png";

const sf::Vector2f menuposition(100.f * Game::Width / 1280, 30.f * Game::Height / 960);

GameOverScreen::GameOverScreen(std::size_t score) : score_(score) ,
	quitbutton1(quitbuttonposition, otherbuttonscale, quitfilename1), quitbutton2(quitbuttonposition, otherbuttonscale, quitfilename2),
	restartbutton1(restartbuttonposition, otherbuttonscale, restartfilename1), restartbutton2(restartbuttonposition, otherbuttonscale, restartfilename2)
{
	font_.loadFromFile("materials/Fonts/segoepr.ttf");
	text_.setFont(font_);
	text_.setString("Your score: " + std::to_string(score) + "!");
	text_.setColor(Game::GlobalTextColor);
	text_.setCharacterSize(75);
	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 3);

	menu = TextButton(menuposition, std::string("Menu"));
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	if (restartbutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		Game::Screen = std::make_shared<GameScreen>();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return;
	}

	if (quitbutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		window.close();
	
	if (menu.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		Game::Screen = std::make_shared<MenuScreen>();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return;
	}
}

void GameOverScreen::update(sf::Time delta, sf::Time& generatefruitflag)
{

}

void GameOverScreen::render(sf::RenderWindow& window)
{
	window.clear(Game::GlobalBGColor);

	if (!quitbutton1.MouseOnButton(window))quitbutton1.render(window);
	else quitbutton2.render(window);

	if (!restartbutton1.MouseOnButton(window))restartbutton1.render(window);
	else restartbutton2.render(window);

	menu.render(window);
	window.draw(text_);
}