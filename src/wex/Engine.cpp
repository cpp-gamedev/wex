#include "SFML/Window/Keyboard.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <wex/Engine.hpp>

namespace wex {

Engine::Status Engine::run() {
	sf::RenderWindow window(sf::VideoMode(mWindowDim.x, mWindowDim.y), mConfig.winTitle);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(mConfig.fps);
	loop(window);
	return Status::ok;
}

void Engine::handleEvents(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed: window.close(); break;
		case sf::Event::KeyPressed: std::cout << "key" << std::endl; break;
		default: break;
		}
	}
}

void Engine::loop(sf::RenderWindow& window) {
	const double msPerFrame = 1000.0 / mConfig.fps;

	double timeThen = 0.0;
	double lag		= 0.0;
	while (window.isOpen()) {
		double timeNow	= 0.0;
		const double dt = timeNow - timeThen;
		timeThen		= timeNow;

		lag += dt;

		handleEvents(window);

		while (lag >= msPerFrame) {
			mDriver->update(dt);
			lag -= msPerFrame;
		}

		window.clear();
		mDriver->draw();
		window.display();
	}
}

} // namespace wex
