#include "OptionScreen.h"
#include "PauseScreen.h"
#include "Game.h"

#include <thread>
#include <chrono>

#include <utility>
using namespace sfSnake;

const sf::Vector2f gobackbuttonposition(75.f * Game::Width / 1280, 75.f * Game::Height / 960);
const sf::Vector2f gobackbuttonscale(0.1f * Game::Width / 1280, 0.1f * Game::Height / 960);

const std::string gobackfilename1 = "materials/buttons/gobackbutton1.png";
const std::string gobackfilename2 = "materials/buttons/gobackbutton2.png";

OptionScreen::OptionScreen(std::shared_ptr<PauseScreen>& pausescreen) :
	gobackbutton1(gobackbuttonposition, gobackbuttonscale, gobackfilename1), gobackbutton2(gobackbuttonposition, gobackbuttonscale, gobackfilename2)
{
	bgcolor = Game::GlobalBGColor;
	pausescreen_ = pausescreen; 

	font_.loadFromFile("materials/Fonts/segoepr.ttf");
	optiontext_.setFont(font_);
	optiontext_.setColor(Game::GlobalTextColor);
	optiontext_.setString("OPTIONS");
	optiontext_.setCharacterSize(100);
	sf::FloatRect textBounds = optiontext_.getLocalBounds();
	optiontext_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	optiontext_.setPosition(Game::Width / 2, 75);

	optionlist_.setFont(font_);
	optionlist_.setColor(Game::GlobalTextColor);
	optionlist_.setString("Grid\n\n\n\nGrid Color\n\n\n\nBG Color");
	optionlist_.setCharacterSize(Game::TextSize);
	optionlist_.setPosition(Game::Width / 10 , Game::Height / 4);

	std::shared_ptr<GameScreen> gamescreen_temp = pausescreen_->GetGameScreen();

	grid_on = TextButton(sf::Vector2f(Game::Width / 3 * 2 - Game::Width / 6, Game::Height / 4), 
		std::string("ON"));
	grid_off = TextButton(sf::Vector2f(Game::Width / 3 * 2 + Game::Width / 6, Game::Height / 4),
		std::string("OFF"));

	if (gamescreen_temp->GetGridState())
		grid_on.ChangeColor(Game::OptionSelectedColor);
	else grid_off.ChangeColor(Game::OptionSelectedColor);

	float line2Height = optionlist_.findCharacterPos(optionlist_.getString().find("Color")).y;
	grid_black = TextButton(sf::Vector2f(Game::Width / 3 * 2 - Game::Width / 4, line2Height),
		std::string("Black"));
	grid_white = TextButton(sf::Vector2f(Game::Width / 3 * 2, line2Height),
		std::string("White"));
	grid_brown = TextButton(sf::Vector2f(Game::Width / 3 * 2 + Game::Width / 4, line2Height),
		std::string("Brown"));

	if (gamescreen_temp->GetGridColor() == sf::Color::Black)
		grid_black.ChangeColor(Game::OptionSelectedColor);
	else if (gamescreen_temp->GetGridColor() == sf::Color::White)
		grid_white.ChangeColor(Game::OptionSelectedColor);
	else grid_brown.ChangeColor(Game::OptionSelectedColor);

	float line3Height = optionlist_.findCharacterPos(optionlist_.getString().find("BG")).y;
	bg_black = TextButton(sf::Vector2f(Game::Width / 3 * 2 - Game::Width / 4, line3Height),
		std::string("Black"));
	bg_white = TextButton(sf::Vector2f(Game::Width / 3 * 2, line3Height),
		std::string("White"));
	bg_brown = TextButton(sf::Vector2f(Game::Width / 3 * 2 + Game::Width / 4, line3Height),
		std::string("Brown"));

	if (Game::GlobalBGColor == sf::Color(255, 250, 240))
		bg_white.ChangeColor(Game::OptionSelectedColor);
	else if (Game::GlobalBGColor == sf::Color::Black)
		bg_black.ChangeColor(Game::OptionSelectedColor);
	else bg_brown.ChangeColor(Game::OptionSelectedColor);
}

OptionScreen::OptionScreen(std::shared_ptr<MenuScreen>& menuscreen, std::shared_ptr<GameScreen>& gamescreen) :
	gobackbutton1(gobackbuttonposition, gobackbuttonscale, gobackfilename1), gobackbutton2(gobackbuttonposition, gobackbuttonscale, gobackfilename2)
{
	bgcolor = Game::GlobalBGColor;
	menuscreen_ = menuscreen;
	gamescreen_ = gamescreen;

	font_.loadFromFile("materials/Fonts/segoepr.ttf");
	optiontext_.setFont(font_);
	optiontext_.setColor(Game::GlobalTextColor);
	optiontext_.setString("OPTIONS");
	optiontext_.setCharacterSize(100);
	sf::FloatRect textBounds = optiontext_.getLocalBounds();
	optiontext_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	optiontext_.setPosition(Game::Width / 2, 75);

	optionlist_.setFont(font_);
	optionlist_.setColor(Game::GlobalTextColor);
	optionlist_.setString("Grid\n\n\n\nGrid Color\n\n\n\nBG Color");
	optionlist_.setCharacterSize(Game::TextSize);
	optionlist_.setPosition(Game::Width / 10, Game::Height / 4);

	grid_on = TextButton(sf::Vector2f(Game::Width / 3 * 2 - Game::Width / 6, Game::Height / 4),
		std::string("ON"));
	grid_off = TextButton(sf::Vector2f(Game::Width / 3 * 2 + Game::Width / 6, Game::Height / 4),
		std::string("OFF"));

	if (gamescreen->GetGridState())
		grid_on.ChangeColor(Game::OptionSelectedColor);
	else grid_off.ChangeColor(Game::OptionSelectedColor);

	float line2Height = optionlist_.findCharacterPos(optionlist_.getString().find("Color")).y;
	grid_black = TextButton(sf::Vector2f(Game::Width / 3 * 2 - Game::Width / 4, line2Height),
		std::string("Black"));
	grid_white = TextButton(sf::Vector2f(Game::Width / 3 * 2, line2Height),
		std::string("White"));
	grid_brown = TextButton(sf::Vector2f(Game::Width / 3 * 2 + Game::Width / 4, line2Height),
		std::string("Brown"));

	if (gamescreen->GetGridColor() == sf::Color::Black)
		grid_black.ChangeColor(Game::OptionSelectedColor);
	else if (gamescreen->GetGridColor() == sf::Color::White)
		grid_white.ChangeColor(Game::OptionSelectedColor);
	else grid_brown.ChangeColor(Game::OptionSelectedColor);

	float line3Height = optionlist_.findCharacterPos(optionlist_.getString().find("BG")).y;
	bg_black = TextButton(sf::Vector2f(Game::Width / 3 * 2 - Game::Width / 4, line3Height),
		std::string("Black"));
	bg_white = TextButton(sf::Vector2f(Game::Width / 3 * 2, line3Height),
		std::string("White"));
	bg_brown = TextButton(sf::Vector2f(Game::Width / 3 * 2 + Game::Width / 4, line3Height),
		std::string("Brown"));

	if (Game::GlobalBGColor == sf::Color(255, 250, 240))
		bg_white.ChangeColor(Game::OptionSelectedColor);
	else if (Game::GlobalBGColor == sf::Color::Black)
		bg_black.ChangeColor(Game::OptionSelectedColor);
	else bg_brown.ChangeColor(Game::OptionSelectedColor);
}

void OptionScreen::handleInput(sf::RenderWindow& window)
{
	if (gobackbutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && pausescreen_ != nullptr)
	{
		Game::Screen = pausescreen_;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return ;
	}

	if (gobackbutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuscreen_ != nullptr)
	{
		Game::Screen = menuscreen_;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return;
	}
	
	if (grid_on.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (grid_on.GetColor() != Game::OptionSelectedColor)
		{
			grid_on.ChangeColor(Game::OptionSelectedColor);
			grid_off.ChangeColor(sf::Color::White);
			if (pausescreen_ != nullptr)
			{
				std::shared_ptr<GameScreen> gamescreen_temp = pausescreen_->GetGameScreen();
				gamescreen_temp->ChangeGridState();
			}
			else gamescreen_->ChangeGridState();
			Game::isgridon = !Game::isgridon;
			return;
		}
	}

	if (grid_off.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (grid_off.GetColor() != Game::OptionSelectedColor)
		{
			grid_off.ChangeColor(Game::OptionSelectedColor);
			grid_on.ChangeColor(sf::Color::White);
			if (pausescreen_ != nullptr)
			{
				std::shared_ptr<GameScreen> gamescreen_temp = pausescreen_->GetGameScreen();
				gamescreen_temp->ChangeGridState();
			}
			else gamescreen_->ChangeGridState();
			Game::isgridon = !Game::isgridon;
			return ;
		}
	}
	
	if (grid_black.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (grid_black.GetColor() != Game::OptionSelectedColor)
		{
			grid_black.ChangeColor(Game::OptionSelectedColor);
			grid_white.ChangeColor(sf::Color::White);
			grid_brown.ChangeColor(sf::Color::White);
			if (pausescreen_ != nullptr)
			{
				std::shared_ptr<GameScreen> gamescreen_temp = pausescreen_->GetGameScreen();
				gamescreen_temp->SetGridColor(sf::Color::Black);
			}
			else gamescreen_->SetGridColor(sf::Color::Black);
			Game::GridColor = sf::Color::Black;
			return;
		}
	}

	if (grid_white.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (grid_white.GetColor() != Game::OptionSelectedColor)
		{
			grid_white.ChangeColor(Game::OptionSelectedColor);
			grid_black.ChangeColor(sf::Color::White);
			grid_brown.ChangeColor(sf::Color::White);
			if (pausescreen_ != nullptr)
			{
				std::shared_ptr<GameScreen> gamescreen_temp = pausescreen_->GetGameScreen();
				gamescreen_temp->SetGridColor(sf::Color::White);
			}
			else gamescreen_->SetGridColor(sf::Color::White);
			Game::GridColor = sf::Color::White;
			return;
		}
	}

	if (grid_brown.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (grid_brown.GetColor() != Game::OptionSelectedColor)
		{
			grid_brown.ChangeColor(Game::OptionSelectedColor);
			grid_white.ChangeColor(sf::Color::White);
			grid_black.ChangeColor(sf::Color::White);
			if (pausescreen_ != nullptr)
			{
				std::shared_ptr<GameScreen> gamescreen_temp = pausescreen_->GetGameScreen();
				gamescreen_temp->SetGridColor(sf::Color(101, 67, 33));
			}
			else gamescreen_->SetGridColor(sf::Color(101, 67, 33));
			Game::GridColor = sf::Color(101,67,33);
			return;
		}
	}

	if (bg_black.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (bg_black.GetColor() != Game::OptionSelectedColor)
		{
			Game::GlobalBGColor = sf::Color::Black;
			Game::GlobalTextColor = sf::Color::White;
			optiontext_.setColor(Game::GlobalTextColor);
			optionlist_.setColor(Game::GlobalTextColor);
			bg_black.ChangeColor(Game::OptionSelectedColor);
			bg_white.ChangeColor(sf::Color::White);
			bg_brown.ChangeColor(sf::Color::White);
			return;
		}
	}

	if (bg_brown.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (bg_brown.GetColor() != Game::OptionSelectedColor)
		{
			Game::GlobalBGColor = sf::Color(101, 67, 33);
			Game::GlobalTextColor = sf::Color::White;
			optiontext_.setColor(Game::GlobalTextColor);
			optionlist_.setColor(Game::GlobalTextColor);
			bg_brown.ChangeColor(Game::OptionSelectedColor);
			bg_white.ChangeColor(sf::Color::White);
			bg_black.ChangeColor(sf::Color::White);
			return;
		}
	}

	if (bg_white.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (bg_white.GetColor() != Game::OptionSelectedColor)
		{
			Game::GlobalBGColor = sf::Color(255, 250, 240);
			Game::GlobalTextColor = sf::Color::Black;
			optiontext_.setColor(Game::GlobalTextColor);
			optionlist_.setColor(Game::GlobalTextColor);
			bg_white.ChangeColor(Game::OptionSelectedColor);
			bg_black.ChangeColor(sf::Color::White);
			bg_brown.ChangeColor(sf::Color::White);
			return;
		}
	}
}

void OptionScreen::update(sf::Time delta, sf::Time& generatefruitflag)
{

}

void OptionScreen::render(sf::RenderWindow& window)
{
	window.clear(Game::GlobalBGColor);
	window.draw(optiontext_);
	window.draw(optionlist_);
	
	grid_on.render(window);
	grid_off.render(window);

	grid_black.render(window);
	grid_white.render(window);
	grid_brown.render(window);
	
	bg_black.render(window);
	bg_brown.render(window);
	bg_white.render(window);

	if (!gobackbutton1.MouseOnButton(window))
		gobackbutton1.render(window);
	else gobackbutton2.render(window);
}