#include <wex/GraphicsController.hpp>

namespace wex {

GraphicsController::GraphicsController(WindowConfig const& config)
	: mConfig(config), mWindow(sf::VideoMode(mWindowDims.x, mWindowDims.y), config.windowTitle) {
	mWindow.setVerticalSyncEnabled(mConfig.vSync);
	mWindow.setFramerateLimit(mConfig.fps);
}

} // namespace wex
