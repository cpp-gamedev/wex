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

		case sf::Event::MouseMoved: {
			mInputState.mousePos = {event.mouseMove.x, event.mouseMove.y};
			break;
		}

		case sf::Event::MouseButtonPressed: {
			const auto& btnEvent  = event.mouseButton;
			KeyState& newKeyState = currentInputState.mouse[btnEvent.button];
			newKeyState			  = setFlag(newKeyState, KeyFlag::Pressed);
			break;
		}

		case sf::Event::MouseButtonReleased: {
			const auto& btnEvent  = event.mouseButton;
			KeyState& newKeyState = currentInputState.mouse[btnEvent.button];
			newKeyState			  = setFlag(newKeyState, KeyFlag::Released);
			break;
		}

		default: break;
		}
	}

	auto updateKeyState = [](KeyState const& currState, KeyState& state) {
		if (isPressed(state) or isHeld(state)) {
			if (isReleased(currState)) {
				state = static_cast<KeyState>(KeyFlag::Released);
			} else {
				state = static_cast<KeyState>(KeyFlag::Held);
			}
		} else {
			state = currState;
		}
	};

	for (size_t i = 0; i < currentInputState.keys.size(); ++i) {
		KeyState& state			  = mInputState.keys[i];
		KeyState const& currState = currentInputState.keys[i];
		updateKeyState(currState, state);
	}

	for (size_t i = 0; i < currentInputState.mouse.size(); ++i) {
		KeyState& state			  = mInputState.mouse[i];
		KeyState const& currState = currentInputState.mouse[i];
		updateKeyState(currState, state);
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
