#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "GameScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5; 

#define Coef 180 / 3.14159265358979323846

sf::Vector2f Unitize(sf::Vector2f number)
{
	number.x = number.x / sqrt(number.x * number.x + number.y * number.y);
	number.y = sqrt(1 - number.x * number.x) * number.y / abs(number.y);
	return number;
}

float CalculateRotation(sf::Vector2f num)
{
	 return atan(num.y / num.x);
}

Snake::Snake() : hitSelf_(false)
{
	direction_ = sf::Vector2f (0.f, -1.f);
	initNodes();

	pickupBuffer_.loadFromFile("materials/Sounds/pickup.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("materials/Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);

	striation_.setFillColor(sf::Color::Black);
	striation_.setSize(sf::Vector2f(SnakeNode::BodyRadius * 0.5, SnakeNode::BodyRadius * 1.5));

	headtexture_.loadFromFile("materials/Head/head3.png");
	head_.setTexture(headtexture_);
	sf::FloatRect Bounds = head_.getGlobalBounds();
	head_.setScale(SnakeNode::BodyRadius * 3 / headtexture_.getSize().x, SnakeNode::BodyRadius * 3 / headtexture_.getSize().y);
	head_.setOrigin(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 2);
}

void Snake::initNodes()
{
	for (int i = 0; i <= 10 * (Snake::InitialSize - 1); ++i)
	{
		sf::Vector2f Initial_Position;
		Initial_Position.x = Game::Width / 2 - SnakeNode::BodyDiameter / 2;
		Initial_Position.y = Game::Height / 2 - SnakeNode::BodyDiameter / 2 + SnakeNode::NodeLen * i;

		nodes_.push_back(Initial_Position);
	}
}

void Snake::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		direction_ = sf::Vector2f(0, -1.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction_ = sf::Vector2f(0, 1.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction_ = sf::Vector2f(-1.f, 0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction_ = sf::Vector2f(1.f, 0);

	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2i MousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f HeadPosition = nodes_[0].getPosition();
		
		direction_.x = MousePosition.x - HeadPosition.x;
		direction_.y = MousePosition.y - HeadPosition.y;
		
		direction_ = Unitize(direction_);
	}
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits, std::unordered_map<Color, int>& fruitnum)
{
	decltype(fruits.begin()) toRemove = fruits.end();
	Color color = Color::Black;

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
		{
			toRemove = it;
			
			pickupSound_.play();
			color = (*toRemove).Getfruitcolor();
			fruitnum.find((*toRemove).Getfruitcolor())->second--;
			fruits.erase(toRemove);
			
			if (color == Color::Red)
				grow(3);
			else if (color == Color::Blue)
				grow(2);
			else if (color == Color::Green)
				grow(1);

			break;
		}
	}
}

void Snake::grow(const int& len)
{
	sf::Vector2f EndPosition = nodes_[nodes_.size() - 1].getPosition();
	sf::Vector2f EndDirection = sf::Vector2f(EndPosition - nodes_[nodes_.size() - 2].getPosition());
	
	EndDirection = Unitize(EndDirection);
	
	for (int j = 1; j <= len; ++j)
	{
		for (int i = 1; i <= 10; ++i)
		{
			nodes_.push_back(SnakeNode(sf::Vector2f(EndPosition.x + i * EndDirection.x,
				EndPosition.y + i * EndDirection.y)));
		}
	}
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];
	
	for (decltype(nodes_.size()) i = 30; i < nodes_.size(); i += 10)
	{
		float xdistance = headNode.getPosition().x - nodes_[i].getPosition().x;
		float ydistance = headNode.getPosition().y - nodes_[i].getPosition().y;
		if (sqrt(xdistance*xdistance + ydistance*ydistance) < SnakeNode::BodyDiameter)
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move() 
{
	int MoveNodes;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		MoveNodes = 2;
	else MoveNodes = 1;

	for (int i = 1; i <= MoveNodes; ++i) 
	{
		nodes_.pop_back();
		nodes_.push_front(
			nodes_[0].getPosition() + direction_ * SnakeNode::NodeLen			
		);
	}
}
void Snake::render(sf::RenderWindow& window) 
{
	float rotation;

	head_.setPosition(nodes_[0].getPosition());
	rotation = atan(-1 * direction_.x / direction_.y) * Coef ;
	if (direction_.y > 0) rotation = 180 + rotation;
	head_.rotate(rotation);
	window.draw(head_);
	head_.rotate(-1 * rotation);

	for (auto i = 10; i < nodes_.size(); i += 10)
	{
		nodes_[i].render(window);
	}

	for (auto i = 10; i < nodes_.size(); i += 10)
	{
		rotation = CalculateRotation(nodes_[i - 1].getPosition() - nodes_[i].getPosition()) * Coef;
		striation_.rotate(rotation);
		striation_.setPosition(nodes_[i].getPosition());
		sf::FloatRect Bounds = striation_.getLocalBounds();
		striation_.setOrigin(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 2);
		window.draw(striation_);
		striation_.rotate(-1 * rotation);
	}
}