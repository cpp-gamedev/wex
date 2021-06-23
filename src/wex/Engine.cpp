#include "SFML/Window/Keyboard.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <wex/Engine.hpp>

namespace wex {

Engine::Status Engine::run() {
	loop();
	return Status::ok;
}

void Engine::handleEvents(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed: window.close(); break;
		case sf::Event::KeyPressed: std::cout << "key pressed\n"; break;
		default: break;
		}
	}
}

void Engine::loop() {
	const double msPerFrame = 1000.0 / mGraphics.mFps;

	double timeThen = 0.0;
	double lag		= 0.0;

	auto& window = mGraphics.mWindow;

	while (mGraphics.mWindow.isOpen()) {
		double timeNow	= 0.0;
		const double dt = timeNow - timeThen;
		timeThen		= timeNow;

		lag += dt;

		handleEvents(window);

		while (lag >= msPerFrame) {
			mGame->update(dt);
			lag -= msPerFrame;
		}

		window.clear();
		mGame->draw(mGraphics);
		window.display();
	}
}

} // namespace wex
