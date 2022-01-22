#pragma once
#include "Common.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include <array>

namespace wex {

using Kbd = sf::Keyboard;
using Mouse = sf::Mouse;

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
	static constexpr size_t MaxMouseBtns = sf::Mouse::ButtonCount;
	std::array<KeyState, Kbd::KeyCount> keys{};
	std::array<KeyState, MaxMouseBtns> mouse{};

	/// \brief Pixel position of the mouse cursor relative to the top left of the window.
	sf::Vector2i mousePos{0, 0};
	float mouseWheelDy = 0;

	inline constexpr bool isKeyPressed(Kbd::Key key) const noexcept {
		return isPressed(keys[key]);
	}

	inline constexpr bool isKeyHeld(Kbd::Key key) const noexcept {
		return isHeld(keys[key]);
	}

	inline constexpr bool isKeyReleased(Kbd::Key key) const noexcept {
		return isReleased(keys[key]);
	}

	inline constexpr bool isMouseBtnPressed(Mouse::Button btn) const noexcept {
		return isPressed(mouse[btn]);
	}

	inline constexpr bool isMouseBtnHeld(Mouse::Button btn) const noexcept {
		return isHeld(mouse[btn]);
	}

	inline constexpr bool isMouseBtnReleased(Mouse::Button btn) const noexcept {
		return isReleased(mouse[btn]);
	}
};

} // namespace wex
