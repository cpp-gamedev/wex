#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: window.close(); break;
			case sf::Event::KeyPressed: std::cout << "ping\n"; break;
			default: break;
			}
		}
		window.clear();
		window.display();
	}
	return EXIT_SUCCESS;
}
