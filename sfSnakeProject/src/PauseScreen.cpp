#include "PauseScreen.h"
#include "GameScreen.h"
#include "Menuscreen.h"
#include "OptionScreen.h"
#include "HelpScreen.h"

#include <string>
#include <thread>
#include <chrono>

using namespace sfSnake;

const sf::Vector2f startbuttonposition(75.f * Game::Width / 1280, 75.f * Game::Height / 960);
const sf::Vector2f startbuttonscale(0.1f * Game::Width / 1280, 0.1f * Game::Height / 960);

const sf::Vector2f otherbuttonscale(0.15f * Game::Width /1280, 0.15f * Game::Height / 960);
const sf::Vector2f optionbuttonposition(Game::Width / 4, Game::Height / 3 * 2);
const sf::Vector2f restartbuttonposition(Game::Width / 2, Game::Height / 3 * 2);
const sf::Vector2f quitbuttonposition(Game::Width / 4 * 3, Game::Height / 3 * 2);

const sf::Vector2f helpbuttonposition(Game::Width - 75.f * Game::Width / 1280, 45.f * Game::Height / 960);

const std::string continuefilename1 = "materials/buttons/start1.png";
const std::string continuefilename2 = "materials/buttons/start2.png";

const std::string quitfilename1 = "materials/buttons/quitbutton1.png";
const std::string quitfilename2 = "materials/buttons/quitbutton2.png";

const std::string restartfilename1 = "materials/buttons/restartbutton1.png";
const std::string restartfilename2 = "materials/buttons/restartbutton2.png";

const std::string optionfilename1 = "materials/buttons/optionbutton1.png";
const std::string optionfilename2 = "materials/buttons/optionbutton2.png";

PauseScreen::PauseScreen(std::shared_ptr<GameScreen>& gamescreen, const int& score) : 
	continuebutton1(startbuttonposition, startbuttonscale, continuefilename1),  continuebutton2(startbuttonposition, startbuttonscale, continuefilename2),
	quitbutton1(quitbuttonposition, otherbuttonscale, quitfilename1), quitbutton2(quitbuttonposition, otherbuttonscale, quitfilename2), 
	restartbutton1(restartbuttonposition, otherbuttonscale, restartfilename1), restartbutton2(restartbuttonposition, otherbuttonscale, restartfilename2),
	optionbutton1(optionbuttonposition, otherbuttonscale, optionfilename1), optionbutton2(optionbuttonposition, otherbuttonscale, optionfilename2)
{
	bgcolor = Game::GlobalBGColor; 
	gamescreen_ = gamescreen;

	font_.loadFromFile("materials/Fonts/segoepr.ttf");
	
	pausetext_.setFont(font_);
	pausetext_.setColor(Game::GlobalTextColor);
	pausetext_.setString("PAUSE"); 
	pausetext_.setCharacterSize(100);
	sf::FloatRect textBounds = pausetext_.getLocalBounds();
	pausetext_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	pausetext_.setPosition(Game::Width / 2, 75);

	scoretext_.setFont(font_);
	scoretext_.setColor(sf::Color::Red);
	scoretext_.setString("Current score : " + std::to_string(score));
	scoretext_.setCharacterSize(50);
	textBounds = scoretext_.getLocalBounds();
	scoretext_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	scoretext_.setPosition(Game::Width / 2, Game::Height / 3);

	helpbutton = TextButton(helpbuttonposition, std::string("Help"));
}

void PauseScreen::handleInput(sf::RenderWindow& window)
{
	if (continuebutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		Game::Screen = gamescreen_;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return;
	}	
	
	if (restartbutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		gamescreen_.reset();
		Game::Screen = std::make_shared<GameScreen>();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return;
	}

	if (quitbutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		gamescreen_.reset();
		Game::Screen = std::make_shared<MenuScreen>();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return;
	}

	if (optionbutton1.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		std::shared_ptr<PauseScreen> pausescreen = std::dynamic_pointer_cast<PauseScreen>(Game::Screen);
		Game::Screen = std::make_shared<OptionScreen>(pausescreen);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return;
	}

	if(helpbutton.MouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		std::shared_ptr<PauseScreen> pausescreen = std::dynamic_pointer_cast<PauseScreen>(Game::Screen);
		Game::Screen = std::make_shared<HelpScreen>(pausescreen);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return;
	}
}

void PauseScreen::update(sf::Time delta, sf::Time& generatefruitflag)
{

}

void PauseScreen::render(sf::RenderWindow& window)
{
	window.clear(Game::GlobalBGColor);
	if (!continuebutton1.MouseOnButton(window))continuebutton1.render(window);
	else continuebutton2.render(window);
	
	if (!quitbutton1.MouseOnButton(window))quitbutton1.render(window);
	else quitbutton2.render(window);

	if (!restartbutton1.MouseOnButton(window))restartbutton1.render(window);
	else restartbutton2.render(window);

	if (!optionbutton1.MouseOnButton(window))optionbutton1.render(window);
	else optionbutton2.render(window);

	pausetext_.setColor(Game::GlobalTextColor);
	window.draw(pausetext_);
	window.draw(scoretext_);

	helpbutton.render(window);
}

 std::shared_ptr<GameScreen> PauseScreen::GetGameScreen()
{
	return gamescreen_;
}