#include <SFML/Graphics.hpp>

#include "SnakeNode.h"
#include <cmath>

using namespace sfSnake;

const float SnakeNode::BodyRadius = 20.f;
const float SnakeNode::BodyDiameter = 1.5 * SnakeNode::BodyRadius;

const float SnakeNode::NodeLen = BodyDiameter / 10;

SnakeNode::SnakeNode(sf::Vector2f position)
: position_(position)
{

	body_.setPosition(position_);
	body_.setFillColor(sf::Color(255, 202, 65));
	body_.setRadius(BodyRadius);
	body_.setOutlineColor(sf::Color::Black);
	body_.setOutlineThickness(-1.f);
	sf::FloatRect Bounds = body_.getLocalBounds();
	body_.setOrigin(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 2);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	body_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	body_.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	body_.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return body_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(body_);
}