#include "SFML/Graphics/CircleShape.hpp"
#include <wex/GraphicsController.hpp>

namespace wex {

GraphicsController::GraphicsController(WindowConfig const& config)
	: mConfig(config), mWindow(sf::VideoMode(mWindowDims.x, mWindowDims.y), config.windowTitle) {
	mWindow.setVerticalSyncEnabled(mConfig.vSync);
	mWindow.setFramerateLimit(mConfig.fps);
}

sf::CircleShape GraphicsController::circle(float x, float y, float radius) {
	sf::CircleShape circle{radius};
	circle.setPosition(x, y);
	return circle;
}

} // namespace wex
