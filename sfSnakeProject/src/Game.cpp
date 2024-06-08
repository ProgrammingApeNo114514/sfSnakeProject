#include <SFML/Graphics.hpp>

#include <random>

#include "MenuScreen.h"
#include "GameScreen.h"
#include "Game.h"

#include <iostream>
#include <typeinfo>
using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 100.f);

sf::Color Game::GlobalBGColor = sf::Color(255, 250, 240);
sf::Color Game::GlobalTextColor = sf::Color::Black;
sf::Color Game::OptionSelectedColor = sf::Color(135, 206, 250);
sf::Color Game::OptionFocusedColor = sf::Color(255, 255, 150);
bool Game::isgridon = true;
sf::Color Game::GridColor = sf::Color::Black;
int Game::TextSize = 40;

std::shared_ptr<Screen> Game::Screen;

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	bgMusic_.openFromFile("materials/Music/bg_music.wav");
	bgMusic_.setLoop	(true);
	bgMusic_.play();
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}

	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta, sf::Time& generatefruitflag)
{
	Game::Screen->update(delta, generatefruitflag);
}

void Game::render()
{
	window_.clear();
	Game::Screen->render(window_);
	window_.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time generatefruitflag = sf::Time::Zero;

	Game::Screen = std::make_shared<MenuScreen>();

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		if (dynamic_cast<MenuScreen*>(Game::Screen.get())) 
			generatefruitflag = sf::Time::Zero;
		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			if(dynamic_cast<GameScreen*>(Game::Screen.get()))
				generatefruitflag += TimePerFrame;
			
			handleInput();
			update(TimePerFrame, generatefruitflag);
		}

		render();
	}
}