#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Shape {

public:

	sf::Text text;
	sf::Vector2f vel;

	Shape(const sf::Text& text, const sf::Vector2f& vel);
};

class WCircle : public Shape {

public:
	sf::CircleShape shape;

	WCircle(const sf::Text& text, const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& color, float radius);
};

class WRectangle : public Shape {

public:
	sf::RectangleShape shape;

	WRectangle(const sf::Text& text, const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& color, const sf::Vector2f& size);
};