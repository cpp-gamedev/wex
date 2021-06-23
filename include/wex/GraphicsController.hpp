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
	std::string windowTitle = "Wex Game";
	float fps				= 60.0;
	u32 winWidth			= 800;
	u32 winHeight			= 600;
	bool vSync				= true;
};

class GraphicsController : util::Pinned {
	friend Engine;

  public:
	explicit GraphicsController(WindowConfig const& config = WindowConfig());

	Circle circle(float x, float y, float radius);

	inline void draw(sf::Drawable const& drawable) {
		mWindow.draw(drawable);
	}

  private:
	WindowConfig mConfig;

  public:
	double mFps = mConfig.fps;
	sf::Vector2u mWindowDims{mConfig.winWidth, mConfig.winHeight};
	sf::RenderWindow mWindow;
};

} // namespace wex
