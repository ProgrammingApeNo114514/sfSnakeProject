#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <unordered_map>
#include <vector>
#include <memory>

#include "Screen.h"
#include "Fruit.h"

namespace sfSnake
{
class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta,sf::Time& generatefruitflag);
	void render();

	static const int Width = 1280;
	static const int Height = 960;

	sf::RenderWindow window_;
	static std::shared_ptr<Screen> Screen;

	static sf::Color GlobalBGColor;
	static sf::Color GlobalTextColor;
	static sf::Color OptionSelectedColor;
	static sf::Color OptionFocusedColor;
	static bool isgridon;
	static sf::Color GridColor;

	static int TextSize;
private:
	sf::Music bgMusic_;

	static const sf::Time TimePerFrame;
};
}


#endif