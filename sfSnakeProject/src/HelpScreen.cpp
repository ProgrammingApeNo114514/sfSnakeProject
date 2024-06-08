#include "HelpScreen.h"

#include <thread>
#include <chrono>

using namespace sfSnake;

const sf::Vector2f gobackbuttonposition(75.f * Game::Width / 1280, 75.f * Game::Height / 960);
const sf::Vector2f gobackbuttonscale(0.1f * Game::Width / 1280, 0.1f * Game::Height / 960);

const std::string gobackfilename1 = "materials/buttons/gobackbutton1.png";
const std::string gobackfilename2 = "materials/buttons/gobackbutton2.png";

HelpScreen::HelpScreen()
{

}

HelpScreen::HelpScreen(std::shared_ptr<PauseScreen>& pausescreen) :
	gobackbutton1(gobackbuttonposition, gobackbuttonscale, gobackfilename1), gobackbutton2(gobackbuttonposition, gobackbuttonscale, gobackfilename2)
{
	pausescreen_ = pausescreen;

	font_.loadFromFile("materials/Fonts/segoepr.ttf");
	helptext_.setFont(font_);
	helptext_.setColor(Game::GlobalTextColor);
	helptext_.setString("HELP");
	helptext_.setCharacterSize(100);
	sf::FloatRect textBounds = helptext_.getLocalBounds();
	helptext_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	helptext_.setPosition(Game::Width / 2, 75);

	contenttext_.setFont(font_);
	contenttext_.setColor(Game::GlobalTextColor);
	contenttext_.setString("Use [W/A/S/D] or the right button of your mouse to \ncontrol the direction of the snake. \nYou can also press [Space] to accelerate.\
										\n\nThere are five kinds of fruit on the screen: \nblack(0), brown(0), red(3), blue(2), green(1)\n\nYou can also change the settings in the OptionScreen.");
	contenttext_.setCharacterSize(Game::TextSize);
	contenttext_.setPosition(Game::Width / 10, Game::Height / 4);
}

HelpScreen::HelpScreen(std::shared_ptr<MenuScreen>& menuscreen) :
	gobackbutton1(gobackbuttonposition, gobackbuttonscale, gobackfilename1), gobackbutton2(gobackbuttonposition, gobackbuttonscale, gobackfilename2)
{
	menuscreen_ = menuscreen;

	font_.loadFromFile("materials/Fonts/segoepr.ttf");
	helptext_.setFont(font_);
	helptext_.setColor(Game::GlobalTextColor);
	helptext_.setString("HELP");
	helptext_.setCharacterSize(100);
	sf::FloatRect textBounds = helptext_.getLocalBounds();
	helptext_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	helptext_.setPosition(Game::Width / 2, 75);

	contenttext_.setFont(font_);
	contenttext_.setColor(Game::GlobalTextColor);
	contenttext_.setString("Use [W/A/S/D] or the right button of your mouse to \ncontrol the direction of the snake. \nYou can also press [Space] to accelerate.\
										\n\nThere are five kinds of fruit on the screen: \nblack(0), brown(0), red(3), blue(2), green(1)\n\nYou can also change the settings in the OptionScreen.");
	contenttext_.setCharacterSize(Game::TextSize);
	contenttext_.setPosition(Game::Width / 10, Game::Height / 4);
}

void HelpScreen::handleInput(sf::RenderWindow& window)
{
	if (gobackbutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && pausescreen_ != nullptr)
	{
		Game::Screen = pausescreen_;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return;
	}

	if (gobackbutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuscreen_ != nullptr)
	{
		Game::Screen = menuscreen_;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return;
	}
}

void HelpScreen::update(sf::Time delta, sf::Time& generatefruitflag)
{

}

void HelpScreen::render(sf::RenderWindow& window)
{
	window.clear(Game::GlobalBGColor);
	window.draw(helptext_);

	window.draw(contenttext_);

	if (!gobackbutton1.MouseOnButton(window))
		gobackbutton1.render(window);
	else gobackbutton2.render(window);
}