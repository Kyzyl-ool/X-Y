#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "vector.cpp"
#include "sfml.cpp"

#define WIDTH 800
#define HEIGHT 600
#define MAXN 100


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
	//~ cout << a.min() << endl;
	
	sf::VertexArray lines(sf::LineStrip, MAXN);
	for (int i = 0; i < MAXN; i++)
	{
		lines[i].position = sf::Vector2f(WIDTH*i/MAXN, HEIGHT-HEIGHT*a[(double)a.length()*i/MAXN]/a.max());
		lines[i].color = sf::Color::White;
	}
	
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "X-Y");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(lines);
		window.display();
	}
	
	return 0;
}
