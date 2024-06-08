#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <iostream>
#include <thread>
#include <chrono>

#include "GameOverScreen.h"
#include "Game.h"
#include "PauseScreen.h"

using namespace sfSnake;

const float generatefruitfrequency = 2.f;
const float UselessFruitRatio = 0.25;

const sf::Vector2f pausebuttonposition(75.f * Game::Width / 1280, 75.f * Game::Height / 960);
const sf::Vector2f scale(0.1f * Game::Width / 1280, 0.1f * Game::Height / 960);

const std::string filename1 = "materials/buttons/pause1.png";
const std::string filename2 = "materials/buttons/pause2.png";

GameScreen::GameScreen() : snake_(), isgridon(Game::isgridon), grid_(50, 1280, 960), pausebutton1(pausebuttonposition, scale, filename1), pausebutton2(pausebuttonposition, scale, filename2)
{
	bgcolor = Game::GlobalBGColor;
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
	if (pausebutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::shared_ptr<GameScreen> gamescreen = std::dynamic_pointer_cast<GameScreen>(Game::Screen);
		Game::Screen = std::make_shared<PauseScreen>(gamescreen, (snake_.getSize() - 1) / 10 + 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void GameScreen::update(sf::Time delta, sf::Time& generatefruitflag)
{
	if (generatefruitflag.asSeconds() >= generatefruitfrequency)
	{
		generatefruitflag = sf::Time::Zero; 
		generateFruit();
	}

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_, fruitnum);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>((snake_.getSize()-1)/10 + 1);
}

void GameScreen::render(sf::RenderWindow& window)
{
	window.clear(Game::GlobalBGColor);
	if (isgridon) grid_.draw(window);
	snake_.render(window);
	for (auto fruit : fruit_)
		fruit.render(window);

	if(!pausebutton1.MouseOnButton(window))pausebutton1.render(window);
	else pausebutton2.render(window);
}

const int GameScreen::GetFruitNum(Color color)
{
	return fruitnum.at(color);
}

void GameScreen::AddFruit(Color color)
{
	fruitnum.find(color)->second++;
}

void GameScreen::DeleteFruit(Color color)
{
	fruitnum.find(color)->second--;
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine;
	engine.seed(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::BodyDiameter);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::BodyDiameter);

	std::uniform_int_distribution<int> colornum;

 	if ((fruitnum.at(Color::Black) + fruitnum.at(Color::Brown)) / UselessFruitRatio < fruit_.size() ) {
		colornum = std::uniform_int_distribution<int>(0, 1);
	}
	else {
		colornum = std::uniform_int_distribution<int>(2, 4);
	}

	switch (colornum(engine))
	{
		case int(Color::Black):
			fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), sf::Color::Black, Color::Black));
			AddFruit(Color::Black);
			break;

		case int(Color::Brown) :
			fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), sf::Color(139,69,19), Color::Brown));
			AddFruit(Color::Brown);
			break;

		case int(Color::Red):
			fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), sf::Color::Red, Color::Red));
			AddFruit(Color::Red);
			break;

		case int(Color::Green):
			fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), sf::Color::Green, Color::Green));
			AddFruit(Color::Green);
			break;

		case int(Color::Blue):
			fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), sf::Color::Blue, Color::Blue));
			AddFruit(Color::Blue);
			break;
	}
}

bool GameScreen::GetGridState()
{
	return isgridon;
}

void GameScreen::ChangeGridState()
{
	isgridon = !isgridon;
}

sf::Color GameScreen::GetGridColor()
{
	return grid_.GetGridColor();
}

void GameScreen::SetGridColor(const sf::Color& color)
{
	grid_.setGridColor(color);
}

