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
	sf::Clock clock;
	auto& window = mGraphics.mWindow;
	while (mGraphics.mWindow.isOpen()) {
		// dt is the time elapsed since the last
		// time 'update' was called.
		const int dt = clock.restart().asMilliseconds();

		handleEvents(window);

		mGame->update(dt);

		window.clear();
		assert(mGame->graphicsController().get() != nullptr);
		mGame->draw();
		window.display();
	}
}

} // namespace wex
