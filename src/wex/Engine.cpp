#include "SFML/System/Clock.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "wex/Input.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <wex/Engine.hpp>

#include <cassert>
#include <iostream>

namespace wex {

Engine::Status Engine::run() {
	assert(mGame.get() != nullptr);
	mGame->init();
	// mGraphics.mWindow.setKeyRepeatEnabled(false);
	loop();
	return Status::ok;
}

/*
	+----------+----------+---------+---------+
	|          | Released | Pressed | Nothing |
	+----------+----------+---------+---------+
	| Released | -        | Pressed | Nothing |
	+----------+----------+---------+---------+
	| Pressed  | Released | Held    | Held    |
	+----------+----------+---------+---------+
	| Held     | Released | Held    | Held    |
	+----------+----------+---------+---------+
	| Nothing  | -        | Pressed | -       |
	+----------+----------+---------+---------+
*/
void Engine::handleEvents(sf::RenderWindow& window) {
	sf::Event event;
	InputState currentInputState;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed: window.close(); break;

		case sf::Event::KeyPressed: {
			const auto keyCode	  = event.key.code;
			KeyState& newKeyState = currentInputState.keys[keyCode];
			newKeyState			  = setFlag(newKeyState, KeyFlag::Pressed);
			break;
		}

		case sf::Event::KeyReleased: {
			const auto keyCode	  = event.key.code;
			KeyState& newKeyState = currentInputState.keys[keyCode];
			newKeyState			  = setFlag(newKeyState, KeyFlag::Released);
			break;
		}

		default: break;
		}
	}

	for (size_t i = 0; i < currentInputState.keys.size(); ++i) {
		KeyState& state			  = mInputState.keys[i];
		KeyState const& currState = currentInputState.keys[i];

		if (isPressed(state) or isHeld(state)) {
			if (isReleased(currState)) {
				state = static_cast<KeyState>(KeyFlag::Released);
			} else {
				state = static_cast<KeyState>(KeyFlag::Held);
			}
		} else {
			state = currState;
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
		mGame->draw();
		window.display();
	}
}

} // namespace wex
