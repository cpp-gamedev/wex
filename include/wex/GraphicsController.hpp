#include "Common.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "util.hpp"

namespace wex {

using Circle = sf::CircleShape;

/// \brief A configuration struct for intializing
/// a wex::GraphicsController.
struct WindowConfig {
	static constexpr u32 DefaultWidth  = 800;
	static constexpr u32 DefaultHeight = 600;

	std::string windowTitle = "Wex Game";
	float fps				= 60.0f;
	u32 winWidth			= 800;
	u32 winHeight			= 600;
	bool vSync				= true;
};

class GraphicsController : util::Pinned {
	friend Engine;

  public:
	explicit GraphicsController(WindowConfig const& config = WindowConfig());

	/// \brief make a circle at position (x, y) with a given radius.
	/// \param x x-coordinate in pixels
	/// \param y y-coordinate in pixels
	/// \param radius radius of the circle in pixels
	[[nodiscard]] Circle circle(float x, float y, float radius);

	/// \brief renders a drawable object to the current RenderWindow.
	inline void draw(sf::Drawable const& drawable) {
		mWindow.draw(drawable);
	}

  private:
	WindowConfig mConfig;

  public:
	float mFps = mConfig.fps;
	sf::Vector2u mWindowDims{mConfig.winWidth, mConfig.winHeight};
	sf::RenderWindow mWindow;
};

} // namespace wex
