#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <wex/Game.hpp>

namespace wex {

void Game::run() {
	sf::RenderWindow window(sf::VideoMode(mWindowDim.x, mWindowDim.y), mWindowTitle);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(mFps);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: window.close(); break;
			case sf::Event::KeyPressed: std::cout << "(key event)\n"; break;
			default: break;
			}
		}
		window.clear();
		window.display();
	}
}

void Game::loop() {
	const double msPerFrame = 1000.0f / mFps;

	double timeThen = 0.0f;
	double lag		= 0;

	while (true) {
		double timeNow	= 0.0f;
		const double dt = timeNow - timeThen;
		timeThen		= timeNow;

		lag += dt;

		while (lag >= msPerFrame) {
			mDriver->update(dt);
			lag -= msPerFrame;
		}

		mDriver->draw();
	}
}

} // namespace wex
