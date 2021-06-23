#include "SFML/System/Clock.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <wex/Engine.hpp>

#include <cassert>
#include <iostream>

namespace wex {

Engine::Status Engine::run() {
	assert(mGame.get() != nullptr);
	mGame->init();
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

	sf::Clock clock;
	double lag = 0.0;

	auto& window = mGraphics.mWindow;
	while (mGraphics.mWindow.isOpen()) {
		const int dt = clock.restart().asMilliseconds();
		lag += dt;

		handleEvents(window);

		while (lag >= msPerFrame) {
			mGame->update(dt);
			lag -= msPerFrame;
		}

		window.clear();
		assert(mGame->graphicsController().get() != nullptr);
		mGame->draw(mGraphics);
		window.display();
	}
}

} // namespace wex
