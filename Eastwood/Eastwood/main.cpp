#include "sfml_libs.h"

#include "SFML/Graphics.hpp"

int main()
{
	sf::VideoMode vm;
	vm.width = 1600;
	vm.height = 900;
	vm.bitsPerPixel = 32;

	sf::RenderWindow window(vm, "Eastwood");

	sf::Event e;
	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::Magenta);
		window.display();
	}

	return 0;
}