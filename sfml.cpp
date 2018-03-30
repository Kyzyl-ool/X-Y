#include <SFML/Graphics.hpp>

void sfRunWindow(int width, int height, std::string header)
{
	sf::RenderWindow window(sf::VideoMode(width, height), header);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.display();
	}
}
