#include <iostream>
#include <SFML/Graphics.hpp>
#include "Shape.h"


Shape::Shape(const sf::Text& text, const sf::Vector2f& vel) 
	: text(text), vel(vel) {}


WCircle::WCircle(const sf::Text& text, const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& color, float radius)
	: Shape(text, vel)
{
	shape = sf::CircleShape(radius);
	shape.setPosition(pos);
	shape.setFillColor(color);
}


WRectangle::WRectangle(const sf::Text& text, const sf::Vector2f& pos, const sf::Vector2f& vel,const sf::Color& color, const sf::Vector2f& size)
	: Shape(text, vel)
{
	shape = sf::RectangleShape(size);
	shape.setPosition(pos);
	shape.setFillColor(color);
}