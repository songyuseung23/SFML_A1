#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>

class MovableShape {
	
public:
	std::shared_ptr<sf::Shape> shape;
	sf::Vector2f velocity;
	std::string name;

	MovableShape(std::shared_ptr<sf::Shape>& shape, const sf::Vector2f& vel, const std::string& name)
		:shape(shape), velocity(vel), name(name) {}
};

enum TokenType {
	Window, Font, Circle, Rectangle
};

// >> operator overloading
std::ifstream& operator>>(std::ifstream& stream, TokenType& token) {
	std::string str;
	stream >> str;

	if (str == "Window")
		token = Window;
	else if (str == "Font")
		token = Font;
	else if (str == "Circle")
		token = Circle;
	else if (str == "Rectangle")
		token = Rectangle;

	return stream;
}

void LoadFromFile( sf::RenderWindow& window, std::vector<MovableShape>& shapes, sf::Font& font, sf::Text& text, const unsigned int fr_limit) {

	const std::string base_path = "Resources/";
	const std::string file_path = base_path + "config.txt";
	std::ifstream file(file_path); 

	// Failed to open file -> terminate program
	if (!file.is_open())
	{
		std::cerr << "Failed to load file : " << file_path;
		return;
	}

	TokenType token;

	while (file >> token) {
		switch (token) {
			case Window:
			{
				float w_width, w_height;
				file >> w_width >> w_height;
				window.create(sf::VideoMode(w_width, w_height), "SFML_A1_Window");
				window.setFramerateLimit(fr_limit);
				break;
			}

			case Font:
			{
				std::string font_file;
				int size, red, green, blue;
				file >> font_file >> size >> red >> green >> blue;
				if (!font.loadFromFile(base_path + font_file))
					std::cerr << "Failed to load font : " << base_path + font_file << "\n";
				text.setCharacterSize(size);
				text.setFont(font);
				text.setFillColor(sf::Color(red, green, blue));
				break;
			}

			case Circle:
			{
				std::string shape_name;
				float pos_x, pos_y, vel_x, vel_y, radius;
				int red, green, blue;
				file >> shape_name >> pos_x >> pos_y >> vel_x >> vel_y >> red >> green >> blue >> radius;
				std::shared_ptr<sf::Shape> shape = std::make_shared<sf::CircleShape>(radius);
				shape->setPosition(pos_x, pos_y);
				shape->setFillColor(sf::Color(red, green, blue));
				shapes.push_back(MovableShape(shape, sf::Vector2f(vel_x, vel_y), shape_name));
				break;
			}

			case Rectangle:
			{
				std::string shape_name;
				float pos_x, pos_y, vel_x, vel_y, size_x, size_y;
				int red, green, blue;
				file >> shape_name >> pos_x >> pos_y >> vel_x >> vel_y >> red >> green >> blue >> size_x >> size_y;
				std::shared_ptr<sf::Shape> shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(size_x, size_y));
				shape->setPosition(pos_x, pos_y);
				shape->setFillColor(sf::Color(red, green, blue));
				shapes.push_back(MovableShape(shape, sf::Vector2f(vel_x, vel_y), shape_name));
				break;
			}
		}
	}
}

void CollisionDetection(std::vector<MovableShape>& shapes, const sf::RenderWindow& window) {
	for (MovableShape& ms : shapes) {

		const sf::Vector2f curr_pos = ms.shape->getPosition();

		float width = ms.shape->getLocalBounds().width;
		float height = ms.shape->getLocalBounds().height;

		if (curr_pos.x + width >= window.getSize().x || curr_pos.x <= 0)
			ms.velocity.x *= -1.0f;
		if (curr_pos.y + height >= window.getSize().y || curr_pos.y <= 0)
			ms.velocity.y *= -1.0f;
	}
}

void Draw(std::vector<MovableShape>& shapes, const sf::Text& text, sf::RenderWindow& window) {
	// draw shapes : shapes, texts
	for (MovableShape& ms : shapes) {
		window.draw(*(ms.shape));

		sf::Text name(text);
		name.setString(ms.name);

		sf::Vector2f shape_pos = ms.shape->getPosition();
		sf::FloatRect shape_bounds = ms.shape->getLocalBounds();
		sf::FloatRect text_bounds = name.getLocalBounds();

		name.setPosition(
			shape_pos.x + (shape_bounds.width - text_bounds.width) / 2,
			shape_pos.y + (shape_bounds.height - text_bounds.height) / 2 - text_bounds.top
		);

		window.draw(name);
	}
}

void Update(std::vector<MovableShape>& shapes) {
	for (MovableShape& ms : shapes) {
		ms.shape->setPosition(ms.shape->getPosition().x + ms.velocity.x, ms.shape->getPosition().y + ms.velocity.y);
	}
}

int main() {

	sf::RenderWindow window;
	std::vector<MovableShape> shapes;
	sf::Font font;
	sf::Text text;

	// 60 frame limits.
	const unsigned int fr_limit = 60;

	// Open file succeed -> load from file.
	LoadFromFile(window, shapes, font, text, fr_limit);

	// window open.
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// initialize window 
		window.clear(sf::Color::Black);

		// draw drawable objects
		Draw(shapes, text, window);

		// collision detection
		CollisionDetection(shapes, window); 

		// update shape position
		Update(shapes);
		
		// display
		window.display();
	}

	return 0;
}