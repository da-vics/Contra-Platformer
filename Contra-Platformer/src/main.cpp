#include"Includes/PagesManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(850, 600), "Contra", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	PagesManager pageManager(&window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			pageManager.HandleEvents(&event);

		}
		pageManager.Display();
	}
}