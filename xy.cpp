#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "vector.cpp"
#include "sfml.cpp"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAXN 100

float scale = 1;

using std::cout;
using std::endl;
int main()
{
	std::ifstream fin("points.txt");
	
	vector <double> a;
	
	while (!fin.eof())
	{
		double tmp;
		fin >> tmp;
		a.append(tmp);
	}
	
	a.dump("a", "stdout");
	// cout << a.min() << endl;
		
	sf::VertexArray lines(sf::LineStrip, MAXN);
	for (int i = 0; i < MAXN; i++)
	{
		lines[i].position = sf::Vector2f(SCREEN_WIDTH*i/MAXN, SCREEN_HEIGHT-SCREEN_HEIGHT*a[(double)a.length()*i/MAXN]/a.max());
		lines[i].color = sf::Color::White;
	}
	
	sf::View view(sf::FloatRect(-SCREEN_WIDTH/2*scale, -SCREEN_HEIGHT/2*scale, SCREEN_WIDTH*scale, SCREEN_HEIGHT*scale));
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), __FILE__);
	window.setVerticalSyncEnabled (true);

	window.setView(view);

	sf::VertexArray Ox(sf::LineStrip, 2);
	Ox[0].position = sf::Vector2f(SCREEN_WIDTH, 0);
	Ox[1].position = sf::Vector2f(-SCREEN_WIDTH, 0);

	sf::VertexArray Oy(sf::LineStrip, 2);
	Oy[0].position = sf::Vector2f(0, -SCREEN_HEIGHT);
	Oy[1].position = sf::Vector2f(0, SCREEN_HEIGHT);

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::KeyPressed:
				{
					switch (event.key.code)
					{
						case sf::Keyboard::Escape: {window.close(); break; }
						case 27:
						{
							scale -= 0.1;
							window.setView(view = sf::View(sf::FloatRect(-SCREEN_WIDTH/2*scale, -SCREEN_HEIGHT/2*scale, SCREEN_WIDTH*scale, SCREEN_HEIGHT*scale)));
							break;
						}
						case 28:
						{
							scale += 0.1;
							window.setView(view = sf::View(sf::FloatRect(-SCREEN_WIDTH/2*scale, -SCREEN_HEIGHT/2*scale, SCREEN_WIDTH*scale, SCREEN_HEIGHT*scale)));
							break;
						}
						default:
						{
							printf("%d\n", event.key.code);
							break;
						}
					}
					break;
				}
				case sf::Event::Closed:
				{
					window.close();
				}
				// case sf::Event::MouseMoved:
				// {

				// 	sf::Vector2i pos = sf::Mouse::getPosition();
				// 	printf("(%d, %d)\n", pos.x, pos.y);
				// 	break;
				// }

				default: break;
			}
		}
		window.clear();
		window.draw(lines);
		window.draw(Ox);
		window.draw(Oy);
		window.display();
	}
	
	return 0;
}
