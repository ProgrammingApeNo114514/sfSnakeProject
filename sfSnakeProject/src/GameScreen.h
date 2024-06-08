#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"
#include "Game.h"

#include "GameScreen.h"
#include <unordered_map>
#include <stdbool.h>
#include "Grid.h"
#include "Button.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta, sf::Time& generatefruitflag) override;
	void render(sf::RenderWindow& window) override;

	void generateFruit();
	const int GetFruitNum(Color);
	void AddFruit(Color);
	void DeleteFruit(Color);

	bool GetGridState();
	void ChangeGridState();

	sf::Color GetGridColor();
	void SetGridColor(const sf::Color& color);
private:
	Snake snake_;
	std::vector<Fruit> fruit_;
	std::unordered_map<Color, int> fruitnum = { {Color::Black, 0}, {Color::Brown, 0}, {Color::Red, 0}, {Color::Green, 0}, {Color::Blue, 0} };

	sf::Color bgcolor;
	bool isgridon;
	Grid grid_;

	Button pausebutton1;
	Button pausebutton2;
};
}

#endif
