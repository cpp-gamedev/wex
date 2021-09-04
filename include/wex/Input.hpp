#pragma once
#include "Common.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <array>

namespace wex {

using Kbd = sf::Keyboard;

enum class KeyFlag : u8 {
	Released = 0b001,
	Pressed	 = 0b010,
	Held	 = 0b100,
};

using KeyState = u8;

constexpr bool testFlag(KeyState const state, KeyFlag const flag) {
	return state & static_cast<u8>(flag);
}

constexpr KeyState clearFlag(KeyState const state, KeyFlag const flag) {
	return state & ~(static_cast<u8>(flag));
}

[[nodiscard]] inline constexpr KeyState setFlag(KeyState const state, KeyFlag const flag) {
	return state | static_cast<u8>(flag);
}

[[nodiscard]] inline constexpr KeyState isPressed(KeyState const state) {
	return testFlag(state, KeyFlag::Pressed);
}

[[nodiscard]] inline constexpr KeyState isHeld(KeyState const state) {
	return testFlag(state, KeyFlag::Held);
}

[[nodiscard]] inline constexpr KeyState isReleased(KeyState const state) {
	return testFlag(state, KeyFlag::Released);
}

struct InputState {
	static constexpr size_t MaxMouseBtns = 5;
	std::array<KeyState, Kbd::KeyCount> keys{};
	std::array<KeyState, MaxMouseBtns> mouse{};

	sf::Vector2f mousePos{0.0f, 0.0f};
	float mouseWheelDy = 0;
};

} // namespace wex
